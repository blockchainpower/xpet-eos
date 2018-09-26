#include <eosiolib/eosio.hpp>
#include <eosiolib/types.hpp>
#include <eosiolib/contract.hpp>
#include <eosiolib/asset.hpp>
#include <vector>
#include <string>

#define ASSET_SYMBOL S(4, EOS)

#define ADMIN_ACCOUNT N(asdfqaskfjhb)

#define FUND_ACCOUNT N(asdfqaskfjhc)

#define MAX_PETS_COUNT 1000000

#define MAX_PET_0_COUNT 3000

#define FEES_PER 0.05f

#define FEES_FUND_PER 0.5f

#define INVITOR_PER 0.2f

class xpet : public eosio::contract
{
  public:
    xpet(account_name self) : eosio::contract(self),
                              pets(_self, _self),
                              users(_self, _self),
                              adminpets(_self, _self),
                              sales(_self, _self),
                              params(_self, _self),
                              userbonuses(_self, _self)
    {
        if (params.begin() == params.end())
        {
            params.emplace(_self, [&](auto &p) {
                p = param();
            });
        }
        if (userbonuses.begin() == userbonuses.end())
        {
            userbonuses.emplace(_self, [&](auto &p) { p.id = userbonuses.available_primary_key(); });
        }
    };

    // @abi action
    void setattr(account_name admin, uint64_t pet_id, std::string &attr)
    {
        eosio::require_auth(admin);
        eosio_assert(admin == ADMIN_ACCOUNT, "you are not the admin.");

        setAttr_(admin, pet_id, attr);
    }

    // @abi action
    void removepet(account_name admin, uint64_t pet_id)
    {
        eosio::require_auth(admin);
        eosio_assert(admin == ADMIN_ACCOUNT, "you are not the admin.");

        removePet_(admin, pet_id);
    }

    // @abi action
    void addadminpet(account_name admin, uint64_t id, uint64_t generation, std::string &dna, std::string &attr /*, uint64_t weight */)
    {
        eosio::require_auth(admin);
        eosio_assert(admin == ADMIN_ACCOUNT, "you are not the admin.");

        addAdminPet_(id, generation, dna, attr /*, weight*/);
    }

    // @abi action
    void setowner(account_name admin, account_name owner, uint64_t pet_id)
    {
        eosio::require_auth(admin);
        eosio_assert(admin == ADMIN_ACCOUNT, "you are not the admin.");
        eosio_assert(owner != ADMIN_ACCOUNT && owner != FUND_ACCOUNT, "you can not have pet.");

        setOwner_(admin, owner, pet_id);
    }

    // @abi action
    void setinvitor(account_name user, account_name invitor)
    {
        eosio::require_auth(ADMIN_ACCOUNT);
        eosio_assert(invitor != user, "can not invite self.");

        setInvitor_(user, invitor);
    }

    // @abi action
    void userbusiness(account_name buyer, uint64_t pet_id, const eosio::asset &amount)
    {
        eosio::require_auth(buyer);
        eosio_assert(buyer != ADMIN_ACCOUNT && buyer != FUND_ACCOUNT, "you can not have pet.");

        userBusiness_(buyer, pet_id, amount);
    }

    // @abi action
    void salepet(account_name owner, uint64_t pet_id, const eosio::asset &amount)
    {
        eosio::require_auth(owner);

        sale_(owner, pet_id, amount);
    }

    // @abi action
    void unsalepet(account_name owner, uint64_t pet_id)
    {
        eosio::require_auth(owner);

        unsale_(owner, pet_id);
    }

    // @abi action
    void addpetvalue(account_name owner, uint64_t pet_id, eosio::asset amount)
    {
        eosio::require_auth(owner);
        addPetValue_(owner, pet_id, amount);
    }

    // @abi action
    void withdraw(account_name owner, uint64_t pet_id, eosio::asset amount)
    {
        eosio::require_auth(owner);

        withdraw_(owner, pet_id, amount);
    }

    // @abi action
    void getbonus(account_name user)
    {
        eosio::require_auth(user);
        getBonus_(user);
    }

    // @abi action
    void ping()
    {
        ping_();
    }

    ////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////

  private:
    // @abi table pet i64
    struct pet
    {
        uint64_t id;

        uint64_t generation;

        account_name owner;

        std::string dna;

        std::string attr;

        uint64_t weight;

        eosio::asset value;

        EOSLIB_SERIALIZE(pet, (id)(generation)(owner)(dna)(attr)(weight)(value))

        pet() : id(0), generation(0), owner(0), dna(""), attr(""), weight(0), value(0, ASSET_SYMBOL) {}

        account_name primary_key() const
        {
            return id;
        }
    };

    static constexpr account_name PET_TABLE_NAME = N(pet);
    using pet_list = eosio::multi_index<PET_TABLE_NAME, pet>;

    // @abi table user i64
    struct user
    {
        account_name id;

        std::vector<uint64_t> pets;

        account_name invitor;

        EOSLIB_SERIALIZE(user, (id)(pets)(invitor))

        account_name primary_key() const { return id; }

        void addPet(uint64_t pet_id)
        {
            if (std::find(pets.begin(), pets.end(), pet_id) == pets.end())
            {
                eosio_assert(pets.size() < 64, "one can have no more than 64 pets.");
                pets.push_back(pet_id);
            }
        }

        user() : id(0), pets() {}

        void erasePet(uint64_t pet_id) { pets.erase(std::find(pets.begin(), pets.end(), pet_id)); }
    };

    static constexpr account_name USER_TABLE_NAME = N(user);
    using user_list = eosio::multi_index<USER_TABLE_NAME, user>;

    // @abi table adminpet i64
    struct adminpet
    {
        uint64_t id;

        EOSLIB_SERIALIZE(adminpet, (id))

        account_name primary_key() const
        {
            return id;
        }
    };

    static constexpr account_name ADMINPET_TABLE_NAME = N(adminpet);
    using adminpet_list = eosio::multi_index<ADMINPET_TABLE_NAME, adminpet>;

    // @abi table sale i64
    struct sale
    {
        uint64_t id;

        eosio::asset amount;

        EOSLIB_SERIALIZE(sale, (id)(amount))

        account_name primary_key() const
        {
            return id;
        }
    };

    static constexpr account_name SALE_TABLE_NAME = N(sale);
    using sale_list = eosio::multi_index<SALE_TABLE_NAME, sale>;

    // @abi table param
    struct param
    {
        struct petinfo
        {
            uint64_t petcount;
            uint64_t pet0count;

            EOSLIB_SERIALIZE(petinfo, (petcount)(pet0count));
            petinfo() : petcount(0), pet0count(0) {}
        };
        struct bonusinfo
        {
            eosio::asset sumbonus;
            uint64_t sumpetweight;

            EOSLIB_SERIALIZE(bonusinfo, (sumbonus)(sumpetweight));

            bonusinfo() : sumbonus(0, ASSET_SYMBOL), sumpetweight(0) {}
        };

        struct hist
        {
            eosio::asset totalbonus;

            eosio::asset invitorbonus;

            EOSLIB_SERIALIZE(hist, (totalbonus)(invitorbonus));

            hist() : totalbonus(0, ASSET_SYMBOL), invitorbonus(0, ASSET_SYMBOL) {}
        };

        account_name id;
        petinfo pet;
        bonusinfo bonus;
        hist history;

        EOSLIB_SERIALIZE(param, (id)(pet)(bonus)(history));

        account_name primary_key() const { return 1; }

        void addSumPetWeight(uint64_t w) { bonus.sumpetweight += w; }
        void addSumBonus(const eosio::asset &b)
        {
            bonus.sumbonus += b;
            history.totalbonus += b;
        }
        void addInvitorBonus(const eosio::asset &b) { history.invitorbonus += b; }
        void addPetCount() { pet.petcount += 1; }
        void addPet0Count() { pet.pet0count += 1; }
        void subpet() { pet.petcount -= 1; }
        void subpet0() { pet.pet0count -= 1; }

        eosio::asset divbonus()
        {
            eosio_assert(bonus.sumbonus.amount >= bonus.sumpetweight, "bonus underflow, please wait.");

            auto div_bonus = bonus.sumbonus.amount / bonus.sumpetweight;

            auto remain = bonus.sumbonus.amount - div_bonus * bonus.sumpetweight;

            bonus.sumbonus = eosio::asset(remain, bonus.sumbonus.symbol);
            return eosio::asset(div_bonus, bonus.sumbonus.symbol);
        }

        bool bonusdivable() const { return bonus.sumbonus.amount >= bonus.sumpetweight; }
    };
    static constexpr account_name PARAM_TABLE_NAME = N(param);
    using param_list = eosio::multi_index<PARAM_TABLE_NAME, param>;

    // @abi table userbonus
    struct userbonus
    {
        uint64_t id;
        struct info
        {
            account_name user;
            uint64_t weight;
            eosio::asset bonus;
            EOSLIB_SERIALIZE(info, (user)(weight)(bonus));

            info() : user(0), weight(0), bonus(0, ASSET_SYMBOL) {}
            info(account_name user) : user(user), weight(0), bonus(0, ASSET_SYMBOL) {}
            info(account_name user, uint64_t weight) : user(user), weight(weight), bonus(0, ASSET_SYMBOL) {}
        };

        std::vector<info> data;

        EOSLIB_SERIALIZE(userbonus, (id)(data));

        account_name primary_key() const { return id; }

        inline void addWeight(account_name user, const uint64_t w)
        {
            auto iter = std::find_if(data.begin(), data.end(), [&](auto &r) { return r.user == user; });
            eosio_assert(iter != data.end(), "can't find user weight");
            eosio_assert(iter->weight + w > iter->weight, "weight overflow.");
            iter->weight += w;
        }

        inline void subWeight(account_name user, const uint64_t w)
        {
            auto iter = std::find_if(data.begin(), data.end(), [&](auto &r) { return r.user == user; });
            eosio_assert(iter != data.end(), "can't find user weight");
            eosio_assert(iter->weight >= w, "weight underflow.");
            iter->weight -= w;
        }

        inline eosio::asset withdraw(account_name user)
        {
            auto iter = std::find_if(data.begin(), data.end(), [&](auto &r) { return r.user == user; });
            eosio_assert(iter != data.end(), "can't find user bonus");
            auto tmp = iter->bonus;
            iter->bonus -= tmp;
            return tmp;
        }

        inline void subBonus(account_name user, const eosio::asset &b)
        {
            auto iter = std::find_if(data.begin(), data.end(), [&](auto &r) { return r.user == user; });
            eosio_assert(iter != data.end(), "can't find user bonus");
            iter->bonus -= b;
            eosio_assert(iter->bonus.amount > 0, "bonus underflow");
        }

        inline void addBonusAllUsers(const eosio::asset &b)
        {
            for (auto &r : data)
            {
                r.bonus += b * r.weight;
            }
        }

        inline void addUserWithWeight(account_name user, uint64_t weight)
        {

            auto iter = std::find_if(data.begin(), data.end(), [&](auto &r) { return r.user == user; });
            eosio_assert(iter == data.end(), "user already exist");

            data.push_back({user, weight});
        }
    };
    static constexpr account_name USERBONUS_TABLE_NAME = N(userbonus);
    using userbonus_list = eosio::multi_index<USERBONUS_TABLE_NAME, userbonus>;

    pet_list pets;
    user_list users;
    adminpet_list adminpets;
    sale_list sales;
    param_list params;
    userbonus_list userbonuses;

    ////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////

    inline void userCheck_(account_name user) const;

    inline void petCountCheck_() const;

    inline void pet0CountCheck_() const;

    inline void petCountInc_();

    inline void pet0CountInc_();

    inline void petCountDec_();

    inline void pet0CountDec_();

    inline void sumBonusAdd_(const eosio::asset &bonus);

    inline void sumInvitorBonusAdd_(const eosio::asset &bonus);

    inline void sumPetWeightAdd_(uint64_t weight);

    inline void petCheck_(uint64_t pet) const;

    inline void offerCheck_(const eosio::asset &offer) const;

    inline void addUser_(account_name user, account_name invitor);

    inline void addUserWithPet_(account_name user, uint64_t pet_id, uint64_t weight, account_name invitor);

    inline void setPetOwner_(account_name new_owner, uint64_t pet_id);

    inline void transfer_(account_name from, account_name to, const eosio::asset &amount) const;

    inline void transferToBonus_(account_name from, account_name bonus, const eosio::asset &amount) const;

    inline void transferToInvitor_(account_name from, account_name invitor, const eosio::asset &amount) const;

    inline void handleBonusAndInvitor_(account_name from, account_name invitor, eosio::asset &to_bonus_and_invitor);

    inline void transferWithShare_(account_name from, account_name to, const eosio::asset &offer, account_name invitor);

    inline void ping_();

    //////////////////////////////
    //actions
    //////////////////////////////
    inline void addAdminPet_(uint64_t id, uint64_t generation, std::string dna, std::string &attr);

    inline void removePet_(account_name payer, uint64_t pet_id);

    inline void setOwner_(account_name payer, account_name owner, uint64_t pet_id);

    inline void userBusiness_(account_name buyer, uint64_t pet_id, const eosio::asset &amount);

    inline void sale_(account_name owner, uint64_t pet_id, const eosio::asset &amount);

    inline void unsale_(account_name owner, uint64_t pet_id);

    inline void setAttr_(account_name payer, uint64_t pet_id, std::string &attr);

    inline void addPetValue_(account_name payer, uint64_t pet_id, eosio::asset amount);

    inline void withdraw_(account_name owner, uint64_t pet_id, eosio::asset &amount);

    void getBonus_(account_name user);

    void setInvitor_(account_name user, account_name invitor);
};