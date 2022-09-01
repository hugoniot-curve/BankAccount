/*
 * Accounts.h holds information about all bank accounts
*/

#pragma once

#include <iostream>
#include <list>

#include "BankAccount.h"

class Accounts {
public:
    Accounts();
    ~Accounts();

    short create(double initialDeposit);
    short deposit(short account, double deposit);
    short withdraw(short account, double withdraw);
    short close(short account);
    double balance(short account);
    std::list<BankAccount *> listAccounts(void);
    static void printHeader(std::ostream &o);
    void printInfo(std::ostream &o);

protected:
    std::list<BankAccount *> _accounts;
};
