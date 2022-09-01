#include <iostream>
#include <sstream>

#include "CommandLine.h"
#include "BankAccount.h"
#include "Accounts.h"

using namespace std;


int main() {
    bool skip = true;
    if (!skip) {    
        /* This section of code is not interactive, but shows
         * how to use the classes for this project
         */
        BankAccount::printCount();
        Accounts acts = Accounts();
        acts.create(1000.76);
        BankAccount::printCount();
        acts.create(1000.33);
        BankAccount::printCount();
        int e = acts.deposit(1002, 2000);
        if (e > 0) {cout << "bad value" << endl;}
        acts.create(1000);
        e = acts.withdraw(1003, 71.17);
        if (e > 0) {cout << "bad value" << endl;}
        BankAccount::printCount();

        Accounts::printHeader(std::cout);
        acts.printInfo(std::cout);

        std::cout << "Close an account" << std::endl;
        acts.close(1001);
        acts.withdraw(1001, 1000.76);
        acts.close(1001);
        acts.printInfo(std::cout);
        BankAccount::printCount();
    }
    // BankAccount::printCount();

    {
        CommandLine c = CommandLine();
        while (c.askAndDo()) {}
    }

    // BankAccount::printCount();

    return 0;
}
