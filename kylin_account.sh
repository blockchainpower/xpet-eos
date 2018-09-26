# # account: yzeozeuflzyz
# # Private key: 5KGM7Zr8XM9XbpnSPU1Y6BZrVZurryAp3Qi391oHsT1oZKcQvfk
# # Public key: EOS87x3zei82JufK8XUJB4X7iNju2dC6vKqQHRWUNzapaixJTK2wS

# # Create contract account
# cleos-kylin system newaccount --stake-net "1.0000 EOS" --stake-cpu "1.0000 EOS" --buy-ram "1.0000 EOS" 111111111ooo yzeozeuflzyz EOS87x3zei82JufK8XUJB4X7iNju2dC6vKqQHRWUNzapaixJTK2wS EOS87x3zei82JufK8XUJB4X7iNju2dC6vKqQHRWUNzapaixJTK2wS
# # Buy ram
# cleos-kylin system buyram 111111111ooo yzeozeuflzyz '100.0000 EOS'



# cleos-kylin create key                                                
# Private key: 5JkMLjhr1VGBjUK6mZWHWiUi4nKGxaUbDARJt6iRtCgix34Cm8b
# Public key: EOS8FLbiErHaKHQ7DtftidMwX7RG4KQQUMsDSG8E5tBc3s4bPQZ4g
# cleos-kylin system newaccount --stake-net "1.0000 EOS" --stake-cpu "1.0000 EOS" --buy-ram "1.0000 EOS" 111111111ooo yzeozeuflzya EOS8FLbiErHaKHQ7DtftidMwX7RG4KQQUMsDSG8E5tBc3s4bPQZ4g EOS8FLbiErHaKHQ7DtftidMwX7RG4KQQUMsDSG8E5tBc3s4bPQZ4g


# yzeozeuflzyb
# Private key: 5KJRbKTCr85xze1DnKvVWSAuJD1VS2z9NMzwjmjbrWxzVX4Gxjr
# Public key: EOS5HZiY13GVLjqG4AxQ5Rmw1xKMaf9JvCbAGdHW9krPAWiRBZh9s
# cleos-kylin system newaccount --stake-net "30.0000 EOS" --stake-cpu "120.0000 EOS" --buy-ram "80.0000 EOS" 111111111ooo yzeozeuflzyb EOS5HZiY13GVLjqG4AxQ5Rmw1xKMaf9JvCbAGdHW9krPAWiRBZh9s EOS5HZiY13GVLjqG4AxQ5Rmw1xKMaf9JvCbAGdHW9krPAWiRBZh9s
# cleos-kylin set contract yzeozeuflzyb /eoscontracts/xpet -p yzeozeuflzyb
# cleos-kylin set account permission yzeozeuflzyb active '{"threshold": 1,"keys": [{"key": "EOS5HZiY13GVLjqG4AxQ5Rmw1xKMaf9JvCbAGdHW9krPAWiRBZh9s","weight": 1}],"accounts": [{"permission":{"actor":"yzeozeuflzyb","permission":"eosio.code"},"weight":1}]}' owner -p yzeozeuflzyb


# #合约
# {"msg": "succeeded", "keys": {"active_key": {"public": "EOS5X7vcLB2ja6MiinihJazGgnuMvAGDSPpkLbJmLPABGud7Ah5Wu", "private": "5KBR6rH4TeyXvFj4z2FTkQv4Vq28ZQkS8kL3CWULaAkkLpuX2R4"}, "owner_key": {"public": "EOS8bzWS3rkWxkJ34mHKjzMcesQU8KJkHHeo9c2UFUoRWDtWT7buw", "private": "5KQCheh4xVjty5NH1DMfXDqGmadDNKHMD3iexR5Yb1AHDBYHyQo"}}, "account": "asdfqaskfjha"}

# #管理员
# {"msg": "succeeded", "keys": {"active_key": {"public": "EOS7zmuxxWThUmhcMzEiro7q3ogLLxh3uY6gRfkN1qd1JPsDvA2uX", "private": "5JQzYm491gHeGtZsNuLsYBGnH31xeMKRkzEaXxsSZ86AFGVCano"}, "owner_key": {"public": "EOS6cQmqUo8ppuzy5d7VTKs5ZxZNu48Ps6t4sknm76pnMBEqZ56pk", "private": "5JAUe1rSB4ukxEzPXWzv6o4RDrMhzTMS6Ev2hssfr1W4D6EPoNf"}}, "account": "asdfqaskfjhb"}

# #基金
# {"msg": "succeeded", "keys": {"active_key": {"public": "EOS7tfgMZeCziMTibuFVngMPNsMCLQ9Hkb7iwpJ7E9aSG7pxN88M6", "private": "5KZXAEMdXCP55BxigDXGNtp3jNEQiTXHSB41P7wcFwqgSvJrbfK"}, "owner_key": {"public": "EOS8P8cunrkfZg8RmhJhw5pTeJtY1jFiRX1tgceH2RJYDDWc3a6fA", "private": "5J169fWDkyfGBNEkeiDqY3R5ZJ99Ji5rfobsDG6PMB5emotAULH"}}, "account": "asdfqaskfjhc"}

cleos-kylin set account permission asdfqaskfjha active '{"threshold": 1,"keys": [{"key": "EOS5X7vcLB2ja6MiinihJazGgnuMvAGDSPpkLbJmLPABGud7Ah5Wu","weight": 1}],"accounts": [{"permission":{"actor":"asdfqaskfjha","permission":"eosio.code"},"weight":1}]}' owner -p asdfqaskfjha


###### 最新版
#合约
{"msg": "succeeded", "keys": {"active_key": {"public": "EOS7hURXvLqwPTVhXfr7MsTUEh3UE8xcwZMnfejpwqtzfQkQE5Z3t", "private": "5HpMEhxKJ8NtWx87DxcsUzLrZDDFMDnqPngzUN1aq3PFBKQvHyS"}, "owner_key": {"public": "EOS82h366DJKBCwBmfZDP5ojBX6dHHZ1D6UNE8C5CtSZyTrBGodmj", "private": "5JkPsdeM7USQMFV9NXZnpm7SGJpg9To2KLyzTM44tnVNpwpbtS3"}}, "account": "asdfqaskfjhd"}
#管理员
{"msg": "succeeded", "keys": {"active_key": {"public": "EOS7zmuxxWThUmhcMzEiro7q3ogLLxh3uY6gRfkN1qd1JPsDvA2uX", "private": "5JQzYm491gHeGtZsNuLsYBGnH31xeMKRkzEaXxsSZ86AFGVCano"}, "owner_key": {"public": "EOS6cQmqUo8ppuzy5d7VTKs5ZxZNu48Ps6t4sknm76pnMBEqZ56pk", "private": "5JAUe1rSB4ukxEzPXWzv6o4RDrMhzTMS6Ev2hssfr1W4D6EPoNf"}}, "account": "asdfqaskfjhb"}

#基金
{"msg": "succeeded", "keys": {"active_key": {"public": "EOS7tfgMZeCziMTibuFVngMPNsMCLQ9Hkb7iwpJ7E9aSG7pxN88M6", "private": "5KZXAEMdXCP55BxigDXGNtp3jNEQiTXHSB41P7wcFwqgSvJrbfK"}, "owner_key": {"public": "EOS8P8cunrkfZg8RmhJhw5pTeJtY1jFiRX1tgceH2RJYDDWc3a6fA", "private": "5J169fWDkyfGBNEkeiDqY3R5ZJ99Ji5rfobsDG6PMB5emotAULH"}}, "account": "asdfqaskfjhc"}

cleos-kylin set account permission asdfqaskfjhd active '{"threshold": 1,"keys": [{"key": "EOS82h366DJKBCwBmfZDP5ojBX6dHHZ1D6UNE8C5CtSZyTrBGodmj","weight": 1}],"accounts": [{"permission":{"actor":"asdfqaskfjha","permission":"eosio.code"},"weight":1}]}' owner -p asdfqaskfjhd