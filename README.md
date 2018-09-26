# xpet
## 数据库
* pet
```
id: 宠物id
owner: 所属用户
dna: 宠物DNA
attr: 宠物附加信息
```
* user
```
id: 用户id
pets: 用户拥有的宠物id
```
* adminpet
```
id: 宠物id
```
* sale
```
id: 宠物id
amount: 售卖价格
```
* param
```
pet::petcount 总个数
pet::pet0count 初代个数
bonus::sumbonus 未分奖池
bonus::sumpetweight 总pet weight
history::totalbonus 历史总分红
history::invitorbonus 历史邀请者总分红
```
* userbonus
```
data::user 用户名
data::weight 用户宠物权重和
data::bonus 用户现有分红
```  

## 接口说明  
-----------  
### setattr 
* 功能
```
修改宠物附加信息
```
* 参数   
```
admin: 合约账号名
pet_id: 宠物id
attr: 新的附加信息
```

### setinvitor 
* 功能
```
设置邀请人(user没有的话会自动注册)
```
* 参数   
```
user: 用户
invitor: 邀请人
```

### removepet 
* 功能
```
删除宠物
```
* 参数   
```
admin: 合约账号名
pet_id: 宠物id
```

### addadminpet 
* 功能
```
添加一个自由宠物(无用户所属)
```
* 参数   
```
admin: 合约账号名
id： 宠物id
generation: 代数
dna: 该宠物DNA
attr: 该宠物的一些附加信息
```

### setowner 
* 功能
```
修改宠物所属用户
```
* 参数   
```
admin: 合约账号名
owner: 该宠物所属用户
pet_id: 宠物id
```

### userbusiness 
* 功能
```
用户交易(用户唯一能调用接口)
```
* 参数   
```
buyer: 用户名
pet_id: 用户购买宠物id
amount: 出价(用于核对)
```

### salepet 
* 功能
```
用户挂出售卖或修改售卖价格
```
* 参数   
```
owner: 用户名
pet_id: 用户售卖宠物id
amount: 卖价
```

### unsalepet 
* 功能
```
用户取消售卖
```
* 参数   
```
owner: 用户名
pet_id: 用户售卖宠物id
```

### addpetvalue 
* 功能
```
增加宠物价值
```
* 参数   
```
owner: 用户名
pet_id: 用户宠物id
amount: 增加价值（eos）
```

### withdraw 
* 功能
```
宠物价值提现
```
* 参数   
```
owner: 用户名
pet_id: 用户宠物id
amount: 提现价值（eos）
```

### ping 
* 功能
```
检测是否可分红，若可，则分一次
```
* 参数   
```
(无)
```

### getbonus
* 功能
```
提取所有分红
```
* 参数   
```
user: 用户名
```

