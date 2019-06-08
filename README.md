# Auto make coin smart contract in EOS
The EOS smart contracts(accounts 'makecoinbyme' and 'makecoinhere' at Kylin test network) for making coin by yourself.Users should send more than 1 EOS to the contract account 'makecoinbyme' and present the issued token name, amount and precision.

example:

$ cleos -u https://api.kylin.alohaeos.com push action eosio.token transfer '["andygogogogo", "makecoinbyme", "1.0000 EOS", "SGCC10000.00"]' -p andygogogogo@active

Contact me with emial: zgjxncytl@gmial.com or Wechat: building_blockchain




