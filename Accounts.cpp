/*
 * Accounts.cpp holds information about all bank accounts
*/

#include <stdexcept>
#include <sstream>
#include <string>

#include "Accounts.h"
#include "BankAccount.h"


Accounts::Accounts() { }

Accounts::~Accounts(){
    std::list<BankAccount *>::iterator ii;
    for (ii = _accounts.begin(); ii != _accounts.end(); ++ii) {
        BankAccount *b = *ii;
        delete b;
    }
}

short Accounts::create(double initialDeposit){
    BankAccount *b = new BankAccount();
    try {
        b->makeDeposit(initialDeposit);
    }
    catch ( std::invalid_argument ) {
        return -1;
    }
    _accounts.push_back(b);
    return b->getAccountNumber();
}

short Accounts::deposit(short account, double deposit) {
    std::list<BankAccount *>::iterator ii;
    for (ii = _accounts.begin(); ii != _accounts.end(); ++ii) {
        BankAccount *b = *ii;
        if (account == b->getAccountNumber() ) {
            try {
                b->makeDeposit(deposit);
            }
            catch (std::invalid_argument) {
                return 2;
            }
            return 0;
        }
    }
    std::cout << "Account \'" << account << "\' not found." << std::endl;
    return 1;
}

short Accounts::withdraw(short account, double w) {
    std::list<BankAccount *>::iterator ii;
    for (ii = _accounts.begin(); ii != _accounts.end(); ++ii) {
        BankAccount *b = *ii;
        if (account == b->getAccountNumber() ) {
            try {
                b->makeWithdraw(w);
            }
            catch (std::invalid_argument) {
                return 2;
            }
            return 0;
        }
    }
    std::cout << "Account \'" << account << "\' not found." << std::endl;
    return 1;
}

short Accounts::close(short account) {
    std::list<BankAccount *>::iterator ii;
    for (ii = _accounts.begin(); ii != _accounts.end(); ++ii) {
        BankAccount *b = *ii;
        if (account == b->getAccountNumber() ) {
            if (b->getBalance() > 0) {
                std::cout << "This account still has $" << b->getBalance() << " remaining." << std::endl;
                return 2;
            }
            delete b;
            _accounts.erase(ii);
            return 0;
        }
    }
    std::cout << "Account \'" << account << "\' not found." << std::endl;
    return 1;
}

std::list<BankAccount *> Accounts::listAccounts(void) {
    return _accounts;
}

double Accounts::balance(short account) {
    std::list<BankAccount *>::iterator ii;
    for (ii = _accounts.begin(); ii != _accounts.end(); ++ii) {
        BankAccount *b = *ii;
        return b->getBalance();
    }
    std::cout << "Account \'" << account << "\' not found." << std::endl;
    return 0.0;
}

void Accounts::printHeader(std::ostream &o) {
    o << "Account Number \t Balance" << std::endl;
}

void Accounts::printInfo(std::ostream &o) {
    std::list<BankAccount *>::iterator ii;
    for (ii = _accounts.begin(); ii != _accounts.end(); ++ii) {
        BankAccount *b = *ii;
        o << b->getAccountNumber() << "\t\t $" << b->getBalance() << std::endl;
    }
}
