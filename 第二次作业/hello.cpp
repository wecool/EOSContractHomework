#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>
#include <eosiolib/asset.hpp>
#include <eosiolib/action.hpp>
#include <eosiolib/symbol.hpp>
#include <eosiolib/singleton.hpp>
#include <eosiolib/print.hpp>
#include <eosiolib/transaction.hpp>
#include <eosiolib/crypto.h>
#include <eosiolib/dispatcher.hpp>
using namespace eosio;
using namespace std;
class hello : public contract {
  public:
      using contract::contract;

      [[eosio::action]]
      void hi( name user ) {
                print("game start");
                require_auth(_self);
                auto values=user.value;
                print("hello user value:",values);
                print( ",: Hello ,: ", user);
                action(permission_level{_self, name("active")},
                name("eosio.token"), name("transfer"),
                std::make_tuple(_self, user, asset(1, symbol("EOS", 4)),
                                std::string("game send  eos")) ).send();
        }

        [[eosio::action]]
        void delay(string memo){
                 eosio::transaction t{};
                 t.actions.emplace_back(eosio::permission_level(_self, name("active")),
                                       name("homework1st"), name("hi"),
                               std::make_tuple(name("game")));
                t.delay_sec = 1;
                t.send(1, _self, false);
                print("delay end");
        }
        [[eosio::action]]
        void transfer(name from, name to, asset quantity, string memo) {
                print("transfer from ",from);
                eosio_assert(0," transfer error");


        }

        [[eosio::action]]
        void homework2( name user ) {
                print("start homework2");
                require_auth(_self);
                action(permission_level{_self, name("active")},
                name("homework1st"), name("transfer"),
                std::make_tuple(_self, user, asset(100, symbol("WYWY", 4)),
                                std::string("homework1st send WYWY")) ).send();
        }


};


#define EOSIO_DISPATCH_CUSTOM(TYPE, MEMBERS) \
extern "C" { \
   void apply( uint64_t receiver, uint64_t code, uint64_t action ) { \
   auto self = receiver; \
      if(( code == self&&action != name("transfer").value) || (code == name("hello").value) && action == name("transfer").value){\
        switch( action ) { \
            EOSIO_DISPATCH_HELPER( TYPE, MEMBERS ) \
         } \
         /* does not allow destructor of this contract to run: eosio_exit(0); */ \
      } \
   } \
} \


EOSIO_DISPATCH_CUSTOM( hello, (hi)(delay)(transfer)(homework2))