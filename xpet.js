var Eos = require('eosjs')
var Keygen = require('eosjs-keygen').Keygen

var contractName = 'xpet'
var chainId = '38dc6e87bb9f6b33a21dd56b9f2c24813d83c71009077279c8d746fbd0eaf09d'
var data = {
  keys: {
    masterPrivateKey: 'PW5Hu1DPa43bHLV72QVJAyhar7yRQYfmxighRHeRSZ1M5dsCAznnH',
    privateKeys: {
      owner: '5JhsLsJNYSz13oN7vWSbMMKYWnSGmSjb7E3Tu7EzFdtB6gSqdmv',
      active: '5HxjRxnXxbeUnXQcUx6Nh9Fv8xFoD7Qa7d54dHRXqSLSYRyoJ2F' },
    publicKeys: {
      owner: 'EOS8C62EoSppjzP8MDSAxh6JfkP7VLuqY5zHh9jc7PqfKcGAREfop',
      active: 'EOS7ULrPmvyNvgXzWr7zw1HUmdC3Wy46otcoMFQkgymKTTdzePK5p' } },
  username: 'ice2' }

var admin = {
  name: 'xpet',
  keys: {
    privateKeys: {
      owner: '5Hsrt4f3zJGi62yAwCo6L6zbUwfNqta96GTMhMqQF6hPMaa1KZe',
      active: '5HuzMJxBHEigaqYeJCgEY5zSCG4C4NxixNktWedvJVndxP5YRbD'
    },
    publicKeys: {
      owner: 'EOS6coocvDTLXDpcS15nVpjhbgWCd8os4DuWN8EMZc8mDmmMtGgwd',
      active: 'EOS7ezcrCjxM6hCzYTk3SNhnZG8UrAGwMb4DqKvxxYGZDDy1D2343'
    }
  }
}
// var eos = Eos({
//   keyProvider: this.user.keys.privateKeys.active,
//   sign: true,
//   chainId: chainId
// })

function createAccount (username) {
  console.log('eosjs: createAccount...')
  data.username = username
  Keygen.generateMasterKeys().then(keys => {
    data.keys = keys
    var wif = admin.keys.privateKeys.active
    var eos = Eos({
      keyProvider: wif,
      sign: true,
      chainId: chainId
    })
    var userOwnerPubkey = keys.publicKeys.owner
    var userActivePubkey = keys.publicKeys.active
    console.log(data)
    eos.transaction(tr => {
      tr.newaccount({
        creator: admin.name,
        name: username,
        owner: userOwnerPubkey,
        active: userActivePubkey
      })
      var uaccount = {
        username: username,
        keys: keys
      }

      // tr.transfer({from: 'fenda', to: this.username, quantity: '1 SEK', memo: this.username})
      regist(username)
      // this.$store.dispatch(constants.ACTION_TYPES.CREATE_EOS_ACCOUNT, uaccount)
      // dao.setItem(constants.USER_INFO, uaccount)
      // this.updateAuth()
      // tr.buyrambytes({
      //   payer: 'xpet',
      //   receiver: username,
      //   bytes: 8192
      // })
      // tr.delegatebw({
      //   from: 'xpet',
      //   receiver: username,
      //   stake_net_quantity: '100.0000 SYS',
      //   stake_cpu_quantity: '100.0000 SYS',
      //   transfer: 0
      // })
    })
  })
}
// createAccount('ice3')
function regist (desc = '') {
  console.log(data)
  var eos = Eos({
    keyProvider: data.keys.privateKeys.active,
    sign: true,
    chainId: chainId
  })
  let auth = `${data.username}@active`
  console.log(auth)
  eos.contract(contractName).then((xpet) => {
    xpet.regist(data.username, desc, {
      authorization: [auth],
    }).then((res) => {
      console.log(res)
    }).catch((err) => {
      console.log(err)
    })
  })
}
// regist()
function addPet (owner, dna, attr) {
  var eos = Eos({
    keyProvider: admin.keys.privateKeys.active,
    sign: true,
    chainId: chainId
  })
  eos.contract(contractName).then((xpet) => {
    xpet.addpet(admin.name, owner, dna, attr, {
      authorization: [admin.name]
    }).then((res) => {
      console.log(res)
    }).catch((err) => {
      console.log(err)
    })
  })
}
// addPet('ice')
function setPet (pet_id, attr) {
  var eos = Eos({
    keyProvider: admin.keys.privateKeys.active,
    sign: true,
    chainId: chainId
  })
  eos.contract(contractName).then((xpet) => {
    xpet.setattr(admin.name,pet_id, attr, {
      authorization: [admin.name]
    }).then((res) => {
      console.log(res)
    }).catch((err) => {
      console.log(err)
    })
  })
}

// setPet(1, 'aaa')
function removePet (pet_id) {
  var eos = Eos({
    keyProvider: admin.keys.privateKeys.active,
    sign: true,
    chainId: chainId
  })
  eos.contract(contractName).then((xpet) => {
    xpet.removepet(admin.name, pet_id, {
      authorization: [admin.name]
    }).then((res) => {
      console.log(res)
    }).catch((err) => {
      console.log(err)
    })
  })
}

// removePet(2)

function addAdminPet (dna, attr) {
  var eos = Eos({
    keyProvider: admin.keys.privateKeys.active,
    sign: true,
    chainId: chainId
  })
  eos.contract(contractName).then((xpet) => {
    xpet.addadminpet(admin.name, dna, attr, {
      authorization: [admin.name]
    }).then((res) => {
      console.log(res)
    }).catch((err) => {
      console.log(err)
    })
  })
}

// addAdminPet('111', 'free')

function setOwner (owner, pet_id) {
  var eos = Eos({
    keyProvider: admin.keys.privateKeys.active,
    sign: true,
    chainId: chainId
  })
  eos.contract(contractName).then((xpet) => {
    xpet.setowner(admin.name, owner, pet_id, {
      authorization: [admin.name]
    }).then((res) => {
      console.log(res)
    }).catch((err) => {
      console.log(err)
    })
  })
}

// setOwner ('ice2', 1)

function salePet (owner, pet_id, amount) {
  console.log(owner)
  var eos = Eos({
    keyProvider: owner.keys.privateKeys.active,
    sign: true,
    chainId: chainId
  })
  eos.contract(contractName).then((xpet) => {
    xpet.salepet(owner.username, pet_id, amount, {
      authorization: [owner.username]
    }).then((res) => {
      console.log(res)
    }).catch((err) => {
      console.log(err)
    })
  })
}

// salePet(data, 1, '123.000 EOS')

function unSalePet (owner, pet_id) {
  console.log(owner)
  var eos = Eos({
    keyProvider: owner.keys.privateKeys.active,
    sign: true,
    chainId: chainId
  })
  eos.contract(contractName).then((xpet) => {
    xpet.unsalepet(owner.username, pet_id, {
      authorization: [owner.username]
    }).then((res) => {
      console.log(res)
    }).catch((err) => {
      console.log(err)
    })
  })
}
// unSalePet(data, 1)

function userbusiness (buyer, pet_id, amount) {
  var eos = Eos({
    keyProvider: buyer.keys.privateKeys.active,
    sign: true,
    chainId: chainId
  })
  eos.contract(contractName).then((xpet) => {
    xpet.userbusiness(buyer.username, pet_id, amount,{
      authorization: [buyer.username]
    }).then((res) => {
      console.log(res)
    }).catch((err) => {
      console.log(err)
    })
  })
}

userbusiness(data, 1, '123.000 EOS')