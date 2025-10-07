#ifndef CHECKINGACCOUNT_H
#define CHECKINGACCOUNT_H

#include "BankAccount.h"

class CheckingAccount : public BankAccount {
private:
    double transactionFee;

public:
    CheckingAccount(const string& accNum, const string& holder,
                    double initialBalance, double fee);

    void withdraw(double amount) override;
    void printAccount() const override;
};

#endif
