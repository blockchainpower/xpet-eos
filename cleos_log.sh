cleos create account eosio eosio.token EOS56VyBWT3H7GfZ8AYGU8quJjiDSv7FVJhJzpuXPZNargT6hCDPy EOS56VyBWT3H7GfZ8AYGU8quJjiDSv7FVJhJzpuXPZNargT6hCDPy
cleos set contract eosio.token /opt/eosio/bin/eos-contracts/contracts/eosio.token
cleos push action eosio.token create '[ "eosio", "1000000000.0000 EOS", 0, 0, 0]' -p eosio.token
cleos create account eosio xpet EOS5cYSk1zgjHD89Hu1o1e1cW9iDGveWcKNpwBZYLeaTky4989xjs EOS5cYSk1zgjHD89Hu1o1e1cW9iDGveWcKNpwBZYLeaTky4989xjs
cleos set contract xpet /contracts/xpet -p xpet
cleos set account permission xpet active '{"threshold": 1,"keys": [{"key": "EOS5cYSk1zgjHD89Hu1o1e1cW9iDGveWcKNpwBZYLeaTky4989xjs","weight": 1}],"accounts": [{"permission":{"actor":"xpet","permission":"eosio.code"},"weight":1}]}' owner -p xpet
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
cleos push action xpet addadminpet '["xpet",1,0,"dna","pet No1."]' -p xpet
cleos push action xpet addadminpet '["xpet",2,1,"dna","pet No2."]' -p xpet
cleos push action xpet addadminpet '["xpet",3,0,"dna","pet No3."]' -p xpet
cleos push action xpet addadminpet '["xpet",4,1,"dna","pet No4."]' -p xpet
cleos push action xpet addadminpet '["xpet",5,0,"dna","pet No5."]' -p xpet
cleos push action xpet addadminpet '["xpet",6,1,"dna","pet No6."]' -p xpet
cleos push action xpet addadminpet '["xpet",7,0,"dna","pet No7."]' -p xpet
cleos push action xpet addadminpet '["xpet",8,1,"dna","pet No8."]' -p xpet
cleos push action xpet setattr '["xpet",8,"pet No8. Suuuuuuuuuuuupppppppeeeeerr Veeeeerrrrrssssionnnn!!!!!"]' -p xpet
cleos push action xpet setowner '["xpet","alice",1]' -p xpet
cleos push action xpet setowner '["xpet","bob",2]' -p xpet
cleos push action xpet setowner '["xpet","tom",3]' -p xpet
cleos push action xpet setowner '["xpet","jerry",4]' -p xpet
cleos push action xpet salepet '["xpet",5,"10.0000 EOS"]' -p xpet
cleos push action xpet salepet '["xpet",5,"99.0000 EOS"]' -p xpet
cleos push action xpet unsalepet '["xpet",5]' -p xpet
cleos push action xpet salepet '["xpet",5,"99.0000 EOS"]' -p xpet

cleos push action xpet setinvitor '["alice","bob"]' -p xpet

cleos push action xpet userbusiness '["alice",5,"99.0000 EOS"]' -p alice
cleos push action xpet salepet '["alice",5,"1000.0000 EOS"]' -p alice
cleos push action xpet userbusiness '["bob",5,"1000.0000 EOS"]' -p bob
cleos push action xpet addpetvalue '["bob",5,"888.8888 EOS"]' -p bob
cleos push action xpet addpetvalue '["bob",5,"888.8888 EOS"]' -p bob
cleos push action xpet withdraw '["bob",5,"888.8888 EOS"]' -p bob
cleos push action xpet withdraw '["bob",5,"888.8888 EOS"]' -p bob
cleos push action xpet getbonus '["alice"]' -p alice
cleos push action xpet removepet '["xpet",6]' -p xpet