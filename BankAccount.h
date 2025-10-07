#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H

#include <string>
#include <iostream>
#include <vector>
#include "Transaction.h"

using namespace std;

class BankAccount {
protected:
    string accountNumber;
    string accountHolderName;
    double* balance;
    vector<Transaction> transactionHistory; // has-a relationship (composition)

public:
    BankAccount();
    BankAccount(const string& accNum, const string& holder, double initialBalance);
    virtual ~BankAccount();

    virtual void deposit(double amount);
    virtual void withdraw(double amount);
    double getBalance() const;
    string getAccountHolderName() const;
    string getAccountNumber() const;

    virtual void printAccount() const;
    void printHistory() const; // NEW METHOD
};

#endif
