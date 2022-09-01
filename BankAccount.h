/*
 * BankAccount.h holds bank account information
*/

#pragma once

class BankAccount {
public:
    BankAccount();
    ~BankAccount();

    static void printCount(void);

    short getAccountNumber(void);
    double getBalance(void);
    double makeDeposit(double amnt);
    double makeWithdraw(double amnt);
    double close(void);

protected:
    static short _count;
    static short _initialAccountNumber;
    const short _accountNumber;
    double _balance;
};
