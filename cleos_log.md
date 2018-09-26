# 准备工作
## 参数设置
本测试中，基金账号与管理员账号与合约账号相同，实际可自行更改后编译
## 密钥(公钥)
```
  "EOS56VyBWT3H7GfZ8AYGU8quJjiDSv7FVJhJzpuXPZNargT6hCDPy",
  "EOS5cYSk1zgjHD89Hu1o1e1cW9iDGveWcKNpwBZYLeaTky4989xjs",
  "EOS5dCtDJ1kU4wCSNX32AhiAyka5wE1CZsBTjvbb3UWU8bYwzak5Z",
  "EOS5gT2sQhBz6SRkzqDAfyVTT4Jt9BDy7rMqTKRVa4LfPry3ZkMot",
  "EOS5nWRCg3MEHH1iUS2rnkGi3fTPHZrSJCauRMssCmZ1UqU2Ev4v3",
  "EOS5xV9Fs5yNfaJRUNbKRhc1kTeYo7WfbnWBc2g1bvSdQtAozZ8wL",
  "EOS5yQfN3La5nrSBZkXumxvpTFg19WSRfXL3899A1bdbUnijA6ZJV",
  "EOS6CVVt9GQv9URHKhFTeTjB1YvYpcd9hW87zLg76kHw5dhNKm5qS",
  "EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV",
  "EOS6YfE72qTMkMdQ5CFaWbiMiHibRshRubtVbLLV8F4bssE8ZTvur",
  "EOS6mkhmfHVYYFQyi9zK6opv7EV3DnKpgJCjBeQzgq5mHeFYdG8bT",
  "EOS6rXgxGTZJEuruTV6So3MubUFmjZdvdZCHNzFbcAdRz5WTrt8z9",
  "EOS7JHm18xBFWKL9TZGmn5zycD13opgFFJSJsWMb7QMBQkFUzSurq",
  "EOS7MK3jeVPYuKCadgDxqzq4dpobLE4trjicpqXz6MYjg42ZAj5Jp",
  "EOS7gpeednuaa4iRf3JxwxfxKHgWZ9jGxwbeeemdVSWBwfPJixBqF",
  "EOS7gsztip3QNhStdTifAcfaXcvuqX3prhN9kmdvPki2xFg7nVroe",
  "EOS7vhqZ1hSur76hJB6FTVXfbQE1EGxKhrMiF9bnC8sbsFj5YMFyt",
  "EOS7z5bCydGS8vWyzV5Zf6CgCj1azKS1e3z1f2peznzbyWcUNgfVu",
  "EOS8P3XL51RbTp5WHQma4LZqGYCENTEWT21Vwyr2D5AeMg3bWeSsv",
  "EOS8Q3VKuBLGqLydwbmCiQtYnh8s5cFTdrDabJPt7Pf4GCvNqMjzn",
  "EOS8aLUk7RVZx5Y4yrSNHgLnufVzCv6sUuMzhB7Us3xX3S7RLUG7F",
  "EOS8avuuzE9vVKbg3BonDki1niindFDYg38FbWWUD7jeKr9sWAHWZ",
  "EOS8gP4LQWiz85jEi1mmWBDKU5ehLZF2fmg7UwnXaXNfJoDbjsExv"
```
## EOS
```
cleos create account eosio eosio.token EOS56VyBWT3H7GfZ8AYGU8quJjiDSv7FVJhJzpuXPZNargT6hCDPy EOS56VyBWT3H7GfZ8AYGU8quJjiDSv7FVJhJzpuXPZNargT6hCDPy
cleos set contract eosio.token /opt/eosio/bin/eos-contracts/contracts/eosio.token
cleos push action eosio.token create '[ "eosio", "1000000000.0000 EOS", 0, 0, 0]' -p eosio.token
```
## Contract
```
cleos create account eosio xpet EOS5cYSk1zgjHD89Hu1o1e1cW9iDGveWcKNpwBZYLeaTky4989xjs EOS5cYSk1zgjHD89Hu1o1e1cW9iDGveWcKNpwBZYLeaTky4989xjs
cleos set contract xpet /contracts/xpet -p xpet
cleos set account permission xpet active '{"threshold": 1,"keys": [{"key": "EOS5cYSk1zgjHD89Hu1o1e1cW9iDGveWcKNpwBZYLeaTky4989xjs","weight": 1}],"accounts": [{"permission":{"actor":"xpet","permission":"eosio.code"},"weight":1}]}' owner -p xpet

```
## User
```
cleos create account eosio alice EOS5dCtDJ1kU4wCSNX32AhiAyka5wE1CZsBTjvbb3UWU8bYwzak5Z EOS5dCtDJ1kU4wCSNX32AhiAyka5wE1CZsBTjvbb3UWU8bYwzak5Z
cleos create account eosio bob EOS5gT2sQhBz6SRkzqDAfyVTT4Jt9BDy7rMqTKRVa4LfPry3ZkMot EOS5gT2sQhBz6SRkzqDAfyVTT4Jt9BDy7rMqTKRVa4LfPry3ZkMot
cleos create account eosio tom EOS5nWRCg3MEHH1iUS2rnkGi3fTPHZrSJCauRMssCmZ1UqU2Ev4v3 EOS5nWRCg3MEHH1iUS2rnkGi3fTPHZrSJCauRMssCmZ1UqU2Ev4v3
cleos create account eosio jerry EOS5xV9Fs5yNfaJRUNbKRhc1kTeYo7WfbnWBc2g1bvSdQtAozZ8wL EOS5xV9Fs5yNfaJRUNbKRhc1kTeYo7WfbnWBc2g1bvSdQtAozZ8wL

cleos push action eosio.token issue '["alice", "10000000.0000 EOS", ""]' -p eosio
cleos push action eosio.token issue '["bob", "10000000.0000 EOS", ""]' -p eosio
cleos push action eosio.token issue '["tom", "10000000.0000 EOS", ""]' -p eosio
cleos push action eosio.token issue '["jerry", "10000000.0000 EOS", ""]' -p eosio

cleos set account permission alice active '{"threshold": 1,"keys": [{"key": "EOS5dCtDJ1kU4wCSNX32AhiAyka5wE1CZsBTjvbb3UWU8bYwzak5Z","weight": 1}],"accounts": [{"permission":{"actor":"xpet","permission":"eosio.code"},"weight":1}]}' owner -p alice
cleos set account permission bob active '{"threshold": 1,"keys": [{"key": "EOS5gT2sQhBz6SRkzqDAfyVTT4Jt9BDy7rMqTKRVa4LfPry3ZkMot","weight": 1}],"accounts": [{"permission":{"actor":"xpet","permission":"eosio.code"},"weight":1}]}' owner -p bob
cleos set account permission tom active '{"threshold": 1,"keys": [{"key": "EOS5nWRCg3MEHH1iUS2rnkGi3fTPHZrSJCauRMssCmZ1UqU2Ev4v3","weight": 1}],"accounts": [{"permission":{"actor":"xpet","permission":"eosio.code"},"weight":1}]}' owner -p tom
cleos set account permission jerry active '{"threshold": 1,"keys": [{"key": "EOS5xV9Fs5yNfaJRUNbKRhc1kTeYo7WfbnWBc2g1bvSdQtAozZ8wL","weight": 1}],"accounts": [{"permission":{"actor":"xpet","permission":"eosio.code"},"weight":1}]}' owner -p jerry
```
## 表数据查询
```
cleos get table xpet xpet pet 
cleos get table xpet xpet user 
cleos get table xpet xpet adminpet
cleos get table xpet xpet sale
cleos get table xpet xpet param
```
# 宠物相关操作
## 添加宠物
```
cleos push action xpet addadminpet '["xpet",1,0,"dna","pet No1."]' -p xpet
cleos push action xpet addadminpet '["xpet",2,1,"dna","pet No2."]' -p xpet
cleos push action xpet addadminpet '["xpet",3,0,"dna","pet No3."]' -p xpet
cleos push action xpet addadminpet '["xpet",4,1,"dna","pet No4."]' -p xpet
cleos push action xpet addadminpet '["xpet",5,0,"dna","pet No5."]' -p xpet
cleos push action xpet addadminpet '["xpet",6,1,"dna","pet No6."]' -p xpet
cleos push action xpet addadminpet '["xpet",7,0,"dna","pet No7."]' -p xpet
cleos push action xpet addadminpet '["xpet",8,1,"dna","pet No8."]' -p xpet
```
## 修改宠物attr
```
cleos push action xpet setattr '["xpet",8,"pet No8. Suuuuuuuuuuuupppppppeeeeerr Veeeeerrrrrssssionnnn!!!!!"]' -p xpet
```
## 设置owner
```
cleos push action xpet setowner '["xpet","alice",1]' -p xpet
cleos push action xpet setowner '["xpet","bob",2]' -p xpet
cleos push action xpet setowner '["xpet","tom",3]' -p xpet
cleos push action xpet setowner '["xpet","jerry",4]' -p xpet
```
## 买卖宠物
### admin卖
```
cleos push action xpet salepet '["xpet",5,"10.0000 EOS"]' -p xpet
cleos push action xpet salepet '["xpet",5,"99.0000 EOS"]' -p xpet
cleos push action xpet unsalepet '["xpet",5]' -p xpet
cleos push action xpet salepet '["xpet",5,"99.0000 EOS"]' -p xpet
```
## 设置邀请人
```
cleos push action xpet setinvitor '["alice","bob"]' -p xpet
```
### User买卖
```
cleos push action xpet userbusiness '["alice",5,"99.0000 EOS"]' -p alice
cleos push action xpet salepet '["alice",5,"1000.0000 EOS"]' -p alice
cleos push action xpet userbusiness '["bob",5,"1000.0000 EOS"]' -p bob
```

## 宠物价值注入与提取
```
cleos push action xpet addpetvalue '["bob",5,"888.8888 EOS"]' -p bob
cleos push action xpet addpetvalue '["bob",5,"888.8888 EOS"]' -p bob
cleos push action xpet withdraw '["bob",5,"888.8888 EOS"]' -p bob
cleos push action xpet withdraw '["bob",5,"888.8888 EOS"]' -p bob
```

## 获取分成
```
cleos push action xpet getbonus '["alice"]' -p alice
```

## 删除宠物
```
cleos push action xpet removepet '["xpet",6]' -p xpet
```