#include "xpet.h"

inline void xpet::
    userCheck_(account_name user) const
{
    auto iter = users.find(user);
    eosio_assert(iter != users.end(), "user check failed.");
}

inline void xpet::
    petCountCheck_() const { eosio_assert(params.begin()->pet.petcount < MAX_PETS_COUNT, "pets count check failed."); }

inline void xpet::
    pet0CountCheck_() const { eosio_assert(params.begin()->pet.pet0count < MAX_PET_0_COUNT, "pet0 count check failed."); }

inline void xpet::
    petCountInc_()
{
    params.modify(params.begin(), _self, [&](auto &p) { p.addPetCount(); });
}

inline void xpet::
    pet0CountInc_()
{
    params.modify(params.begin(), _self, [&](auto &p) { p.addPet0Count(); });
}

inline void xpet::
    petCountDec_()
{
    params.modify(params.begin(), _self, [&](auto &p) { p.subpet(); });
}

inline void xpet::
    pet0CountDec_()
{
    params.modify(params.begin(), _self, [&](auto &p) { p.subpet0(); });
}

inline void xpet::
    sumBonusAdd_(const eosio::asset &bonus)
{
    params.modify(params.begin(), _self, [&](auto &p) { p.addSumBonus(bonus); });
}

inline void xpet::
    sumInvitorBonusAdd_(const eosio::asset &bonus)
{
    params.modify(params.begin(), _self, [&](auto &p) { p.addInvitorBonus(bonus); });
}

inline void xpet::
    sumPetWeightAdd_(uint64_t weight)
{
    params.modify(params.begin(), _self, [&](auto &p) { p.addSumPetWeight(weight); });
}

inline void xpet::
    petCheck_(uint64_t pet) const { eosio_assert(pets.find(pet) != pets.end(), "pet check failed."); }

inline void xpet::
    offerCheck_(const eosio::asset &offer) const
{
    eosio_assert(offer.amount > 0, "amount should be positive");
    eosio_assert(offer.symbol == ASSET_SYMBOL, "only EOS supported.");
}

inline void xpet::
    addUser_(account_name user, account_name invitor)
{
    users.emplace(_self, [&](auto &p) {
        p.id = user;
        p.invitor = invitor;
    });
    userbonuses.modify(userbonuses.begin(), _self, [&](auto &p) {
        p.addUserWithWeight(user, 0);
    });
}

inline void xpet::
    addUserWithPet_(account_name user, uint64_t pet_id, uint64_t weight, account_name invitor)
{
    users.emplace(_self, [&](auto &p) {
        p.id = user;
        p.addPet(pet_id);
        p.invitor = invitor;
    });
    userbonuses.modify(userbonuses.begin(), _self, [&](auto &p) {
        p.addUserWithWeight(user, weight);
    });
}

inline void xpet::
    setPetOwner_(account_name new_owner, uint64_t pet_id)
{
    auto iter_pet = pets.find(pet_id);
    account_name old_owner = iter_pet->owner;

    auto iter_oldowner = users.find(old_owner);
    auto iter_newowner = users.find(new_owner);

    if (iter_newowner == users.end())
    {
        addUserWithPet_(new_owner, pet_id, iter_pet->weight, FUND_ACCOUNT);
    }
    else
    {
        users.modify(iter_newowner, _self, [&](auto &p) { p.addPet(pet_id); });
        userbonuses.modify(userbonuses.begin(), _self, [&](auto &p) {
            p.addWeight(new_owner, iter_pet->weight);
        });
    }

    if (old_owner == ADMIN_ACCOUNT)
    {
        sumPetWeightAdd_(iter_pet->weight);
        adminpets.erase(adminpets.find(pet_id));
    }
    else
    {
        userbonuses.modify(userbonuses.begin(), _self, [&](auto &p) {
            p.subWeight(old_owner, iter_pet->weight);
        });
        users.modify(iter_oldowner, _self, [&](auto &p) { p.erasePet(pet_id); });
    }
    pets.modify(iter_pet, _self, [&](auto &p) {
        p.owner = new_owner;
    });
}

inline void xpet::
    transfer_(account_name from, account_name to, const eosio::asset &amount) const
{
    if (from != to && amount.amount > 0)
    {
        offerCheck_(amount);
        eosio::action(
            eosio::permission_level{from, N(active)},
            N(eosio.token), N(transfer),
            std::make_tuple(from, to, amount, std::string("transfer")))
            .send();
    }
}
inline void xpet::
    transferToBonus_(account_name from, account_name bonus, const eosio::asset &amount) const
{
    transfer_(from, bonus, amount);
}

inline void xpet::
    transferToInvitor_(account_name from, account_name invitor, const eosio::asset &amount) const
{
    transfer_(from, invitor, amount);
}

inline void xpet::
    handleBonusAndInvitor_(account_name from, account_name invitor, eosio::asset &to_bonus_and_invitor)
{
    if (to_bonus_and_invitor.amount > 0)
    {
        auto to_bonus = to_bonus_and_invitor;
        if (invitor != FUND_ACCOUNT)
        {
            eosio::asset to_invitor(to_bonus_and_invitor.amount * INVITOR_PER, to_bonus_and_invitor.symbol);
            to_bonus = to_bonus_and_invitor - to_invitor;
            transferToInvitor_(from, invitor, to_invitor);
            sumInvitorBonusAdd_(to_invitor);
        }
        transferToBonus_(from, _self, to_bonus);
        sumBonusAdd_(to_bonus);
    }
}

inline void xpet::
    transferWithShare_(account_name from, account_name to, const eosio::asset &offer, account_name invitor)
{
    if (to == ADMIN_ACCOUNT || to == FUND_ACCOUNT)
    {
        eosio::asset to_fund(offer.amount * FEES_FUND_PER, offer.symbol);
        transfer_(from, FUND_ACCOUNT, to_fund);

        auto to_bonus_and_invitor = offer - to_fund;
        handleBonusAndInvitor_(from, invitor, to_bonus_and_invitor);
    }
    else
    {
        eosio::asset to_fund_and_bonus_and_invitor(offer.amount * FEES_PER, offer.symbol);

        eosio::asset to_owner(offer.amount - to_fund_and_bonus_and_invitor.amount, offer.symbol);
        transfer_(from, to, to_owner);

        eosio::asset to_fund(to_fund_and_bonus_and_invitor.amount * FEES_FUND_PER, to_fund_and_bonus_and_invitor.symbol);

        transfer_(from, FUND_ACCOUNT, to_fund);

        auto to_bonus_and_invitor = to_fund_and_bonus_and_invitor - to_fund;
        handleBonusAndInvitor_(from, invitor, to_bonus_and_invitor);
    }
}

inline void xpet::
    ping_()
{
    auto iter_param = params.begin();

    if (iter_param->bonusdivable())
    {
        eosio::asset div_bonus;
        params.modify(params.begin(), _self, [&](auto &p) { div_bonus = p.divbonus(); });

        userbonuses.modify(userbonuses.begin(), _self, [&](auto &p) { p.addBonusAllUsers(div_bonus); });
    }
}

//////////////////////////////
//actions
//////////////////////////////
inline void xpet::
    addAdminPet_(uint64_t id, uint64_t generation, std::string dna, std::string &attr /*, uint64_t weight */)
{
    petCountCheck_();
    pet0CountCheck_();

    pets.emplace(_self, [&](auto &p) {
        p.id = id;
        p.generation = generation;
        p.owner = ADMIN_ACCOUNT;
        p.dna = dna;
        p.attr = attr;
        p.weight = generation == 0 ? 10 : 1;
    });

    adminpets.emplace(_self, [&](auto &a) {
        a.id = id;
    });

    petCountInc_();
    if (generation == 0)
        pet0CountInc_();
}

inline void xpet::
    removePet_(account_name payer, uint64_t pet_id)
{
    auto iter_pet = pets.find(pet_id);

    auto owner = iter_pet->owner;

    /* admin can`t remove user`s pet */
    eosio_assert(owner == ADMIN_ACCOUNT, "admin can`t remove user`s pet");

    adminpets.erase(adminpets.find(pet_id));

    auto iter_sale = sales.find(pet_id);
    if (iter_sale != sales.end())
    {
        sales.erase(iter_sale);
    }

    petCountDec_();
    if (iter_pet->generation == 0)
        pet0CountDec_();

    pets.erase(iter_pet);
}

inline void xpet::
    setOwner_(account_name payer, account_name owner, uint64_t pet_id)
{
    /* admin can`t set owner of user`s pet */
    auto iter_pet = pets.find(pet_id);
    eosio_assert(iter_pet->owner == ADMIN_ACCOUNT, "pet already had owner");

    setPetOwner_(owner, pet_id);
}

inline void xpet::
    userBusiness_(account_name buyer, uint64_t pet_id, const eosio::asset &amount)
{
    auto iter_pet = pets.find(pet_id);
    eosio_assert(iter_pet->owner != buyer, "pet belongs to you");

    auto iter_sales = sales.find(pet_id);
    auto offer = iter_sales->amount;
    eosio_assert(offer == amount, "invalid offer.");

    offerCheck_(offer);

    auto iter_buyer = users.find(buyer);
    auto owner = iter_pet->owner;
    if (iter_buyer == users.end())
    {
        addUser_(buyer, FUND_ACCOUNT);
        transferWithShare_(buyer, owner, amount, FUND_ACCOUNT);
    }
    else
    {
        transferWithShare_(buyer, owner, amount, iter_buyer->invitor);
    }
    setPetOwner_(buyer, pet_id);

    sales.erase(iter_sales);

    ping_();
}

inline void xpet::
    sale_(account_name owner, uint64_t pet_id, const eosio::asset &amount)
{
    offerCheck_(amount);

    auto iter_pet = pets.find(pet_id);
    eosio_assert(iter_pet != pets.end(), "pet check failed.");

    eosio_assert(iter_pet->owner == owner, "invalid owner");

    auto iter_sales = sales.find(pet_id);
    if (iter_sales == sales.end())
    {
        sales.emplace(owner, [&](auto &s) {
            s.id = pet_id;
            s.amount = amount;
        });
    }
    else
    {
        sales.modify(iter_sales, owner, [&](auto &s) {
            s.amount = amount;
        });
    }
}

inline void xpet::
    unsale_(account_name owner, uint64_t pet_id)
{
    auto iter_pet = pets.find(pet_id);
    eosio_assert(iter_pet != pets.end(), "pet check failed.");

    eosio_assert(iter_pet->owner == owner, "invalid owner");

    auto iter_sales = sales.find(pet_id);
    eosio_assert(iter_sales != sales.end(), "pet not being saled.");

    sales.erase(iter_sales);
}

inline void xpet::
    setAttr_(account_name payer, uint64_t pet_id, std::string &attr)
{
    auto iter_pet = pets.find(pet_id);
    eosio_assert(iter_pet != pets.end(), "pet check failed.");

    pets.modify(iter_pet, payer, [&](auto &p) {
        p.attr = attr;
    });
}

inline void xpet::
    addPetValue_(account_name payer, uint64_t pet_id, eosio::asset amount)
{
    offerCheck_(amount);
    auto iter_pet = pets.find(pet_id);
    eosio_assert(iter_pet != pets.end(), "pet check failed.");
    eosio_assert(iter_pet->owner == payer, "pet not belongs to you.");

    transfer_(payer, _self, amount);
    pets.modify(iter_pet, _self, [&](auto &p) {
        p.value = p.value + amount;
    });
}

inline void xpet::
    withdraw_(account_name owner, uint64_t pet_id, eosio::asset &amount)
{
    auto iter_sales = sales.find(pet_id);
    eosio_assert(iter_sales == sales.end(), "pet is being saled.");

    offerCheck_(amount);
    auto iter_pet = pets.find(pet_id);
    eosio_assert(iter_pet->owner == owner, "pet not belongs to you.");
    eosio_assert(iter_pet->value >= amount, "not enough value.");

    auto remain = iter_pet->value - amount;
    eosio_assert(remain.amount >= 0, "remain value shouldn`t be negative.");
    pets.modify(iter_pet, _self, [&](auto &p) { p.value = remain; });

    auto &user = users.get(owner, "user check failed.");
    transfer_(_self, owner, amount);
}

void xpet::getBonus_(account_name user)
{

    eosio::asset bonus(0, ASSET_SYMBOL);
    userbonuses.modify(userbonuses.begin(), _self, [&](auto &p) { bonus = p.withdraw(user); });

    transfer_(_self, user, bonus);
}

void xpet::setInvitor_(account_name user, account_name invitor)
{
    auto iter_user = users.find(user);
    if (iter_user == users.end())
    {
        addUser_(user, invitor);
        return;
    }

    eosio_assert(iter_user->invitor == FUND_ACCOUNT, "already had invitor.");

    users.modify(iter_user, _self, [&](auto &u) { u.invitor = invitor; });
}

EOSIO_ABI(xpet, (setattr)(removepet)(addadminpet)(setowner)(setinvitor)(userbusiness)(salepet)(unsalepet)(addpetvalue)(withdraw)(getbonus)(ping))