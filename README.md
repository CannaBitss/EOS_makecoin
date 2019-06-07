# EOS auto make coin smart contract
The EOS smart contracts(accounts makecoinbyme and makecoinhere at Kylin test network) for making coin by yourself.

example:

$ cleos -u https://api.kylin.alohaeos.com push action eosio.token transfer '["andygogogogo", "makecoinbyme", "1.0000 EOS", "SGCC10000.00"]' -p andygogogogo@active
executed transaction: 447f7910dcb324a7faf1d619e194e81aa058bb9c99048380b418a11f868ee450  144 bytes  631 us
#   eosio.token <= eosio.token::transfer        {"from":"andygogogogo","to":"makecoinbyme","quantity":"1.0000 EOS","memo":"SGCC10000.00"}
#  andygogogogo <= eosio.token::transfer        {"from":"andygogogogo","to":"makecoinbyme","quantity":"1.0000 EOS","memo":"SGCC10000.00"}
#  makecoinbyme <= eosio.token::transfer        {"from":"andygogogogo","to":"makecoinbyme","quantity":"1.0000 EOS","memo":"SGCC10000.00"}
#  makecoinhere <= makecoinhere::create         {"issuer":"makecoinbyme","maximum_supply":"10000.00 SGCC"}
#  makecoinhere <= makecoinhere::issue          {"to":"andygogogogo","quantity":"10000.00 SGCC","memo":"issue"}
#  makecoinhere <= makecoinhere::transfer       {"from":"makecoinbyme","to":"andygogogogo","quantity":"10000.00 SGCC","memo":"issue"}
#  makecoinbyme <= makecoinhere::transfer       {"from":"makecoinbyme","to":"andygogogogo","quantity":"10000.00 SGCC","memo":"issue"}
#  andygogogogo <= makecoinhere::transfer       {"from":"makecoinbyme","to":"andygogogogo","quantity":"10000.00 SGCC","memo":"issue"}

$ cleos -u https://api.kylin.alohaeos.com get currency balance makecoinhere andygogogogo SGCC
10000.00 SGCC

