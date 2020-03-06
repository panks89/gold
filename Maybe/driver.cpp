#include <iostream>
#include <string>
#include <memory>
#include "Maybe.h"

using namespace std;

struct Address {
    string street;
    int houseNumber;
    int PIN;
    string state;
};

struct Account {
    string name;
    int id;
    Address *address;
};

int main() {
    unique_ptr<Account> account = make_unique<Account>(Account{"pankaj", 1, nullptr});
    Account *acc {account.get()};
    maybe(acc)
        .with([](auto &x) {
                cout << x->id << " : " << x->name << endl;
                return x->address;
            })
        .execute([](auto &x){
                cout << x->street << ", " << x->houseNumber << endl;
                cout << x->PIN << ", " << x->state << endl;
            });
    unique_ptr<Address> address = make_unique<Address> (Address {"BraveShellStrasse", 9, 04105, "La La Land"} );
    account->address = address.get();
    maybe(acc)
        .with([](auto &x) {
                cout << x->id << " : " << x->name << endl;
                return x->address;
            })
        .execute([](auto &x){
                cout << x->street << ", " << x->houseNumber << endl;
                cout << x->PIN << ", " << x->state << endl;
            });
}
