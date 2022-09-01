/*
 * BankAccount.cpp holds bank account information
*/

#include <iostream>
#include <stdexcept>
#include <sstream>
#include <string>

#include "BankAccount.h"

short BankAccount::_count {};
short BankAccount::_initialAccountNumber = 1000;

BankAccount::BankAccount() : _accountNumber {++_initialAccountNumber} {
    _count += 1;
    _balance = 0;
}

BankAccount::~BankAccount() {
    _count -= 1;
}

void BankAccount::printCount(void) {
    std::cout << "Active accounts: " << _count << std::endl;
}

short BankAccount::getAccountNumber(void) {
    return _accountNumber;
}

double BankAccount::getBalance(void){
    return _balance;
}

double BankAccount::makeDeposit(double amnt) {
    if (amnt < 0) {
        throw std::invalid_argument("Deposit must be positive number.");
    }
    _balance += amnt;
    return getBalance();
}

double BankAccount::makeWithdraw(double amnt) {
    if (amnt < 0) {
        throw std::invalid_argument("Deposit must be positive number.");
    }
    if ( _balance - amnt < 0 ) {
        throw std::invalid_argument("Insufficent funds.");
    }
    _balance -= amnt;
    return getBalance();
}

double BankAccount::close(void) {
    return makeWithdraw( getBalance() );
}
