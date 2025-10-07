#ifndef SAVINGSACCOUNT_H
#define SAVINGSACCOUNT_H

#include "BankAccount.h"

class SavingsAccount : public BankAccount {
private:
    double interestRate;

public:
    SavingsAccount(const string& accNum, const string& holder,
                   double initialBalance, double rate);

    void calculateInterest();
    void printAccount() const override;
};

#endif
