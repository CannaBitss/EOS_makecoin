#include <eosio/eosio.hpp>
#include <eosio/asset.hpp>

using namespace eosio;

class [[eosio::contract("makecoinbyme")]] makecoinbyme : public eosio::contract
{
  public:
    makecoinbyme(name receiver, name code,  datastream<const char*> ds) : contract(receiver, code, ds) {}

   [[eosio::action]]
   void transfer(name from, name to, asset quantity, std::string memo)//接收到transfer命令执行发币
	{
	    	if(from != "makecoinbyme"_n && to == "makecoinbyme"_n && quantity.symbol == symbol("EOS", 4) && quantity.amount >=10000 ) //transfer由makecoinbyme合约发出不会触发造币，接收EOS账户为makecoinbyme合约，接收代币为EOS，数量大于或等于1EOS
	   	 {

			asset quant = memo_analysis(memo);//解析memo中关于造币信息，memo格式如“ABC10000.0000”
                        
			action(
			    permission_level{ "makecoinbyme"_n, "active"_n },
			    "makecoinhere"_n, "create"_n,
			    std::make_tuple("makecoinbyme"_n, quant)
			).send();//内联交易调用makecoinhere合约造币

			action(
			    permission_level{ "makecoinbyme"_n, "active"_n },
			    "makecoinhere"_n, "issue"_n,
			    std::make_tuple(from, quant, std::string("issue"))
			).send();//内联交易调用makecoinhere合约发币给对方

		}

        }
   private:
       asset memo_analysis(const std::string& memo)//通过字符串拆解分析memo中关于造币信息，memo格式如“ABC10000.0000”
           {
                std::string s_a;//保存币名称
                int64_t s_b=0;//保存币总量
		uint8_t s_c=0;//保存币精度
		for(uint8_t i=0,ss=0;memo[i]!='\0' ;i++)//循环遍历memo字符串
		     {  
			  if((memo[i]>64 && memo[i]<91) || (memo[i]>96 && memo[i]<123))//如果为英文字符，则保存在币名中，小写字母会转换为大写
				{   
				        
                                        if(ss==0) //ss记录扫描memo字符串状态，字符为0，数字为1
						{
							if(memo[i]>96 && memo[i]<123)
							{
								s_a.insert(s_a.end(),memo[i]-32);
							}
							else
								s_a.insert(s_a.end(),memo[i]);
						}
				     	
				      

				}
			 if(memo[i]>47 && memo[i]<58)//如果为数字，则保存在币总量中
			       {        if(ss==0)
				        {
				              ss=1;//修改扫描memo字符串状态
                                              s_b = memo[i]-48;
				         }
                                        else if(ss==1)
					{
					      s_b=s_b*10+(memo[i]-48);
					}
				        	    
			       }
			 if(memo[i]==46 && ss==1)//如果为小数点，则计算币精度
			 {
			       s_c=memo.length()-i-1;
			 }
			  
		     }
		
		return {s_b, symbol(s_a, s_c)};//造币信息转换为asset格式并返回
		     
           }
       

};

extern "C"//用于监听eosio.token合约中转账给本合约的信息，并触发本合约transfer造币方法
{ 
   void apply( name receiver, name code, name action ) 
     { 
	      if(code == "eosio.token"_n && action == "transfer"_n) 
		{ 
			eosio::execute_action(eosio::name(receiver), eosio::name(code), &makecoinbyme::transfer);

        	} 
      } 
}




