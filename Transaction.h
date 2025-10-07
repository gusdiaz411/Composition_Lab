#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
using namespace std;

class Transaction {
public:
    string type;
    double amount;
    string timestamp;

    Transaction(const string& type, double amount, const string& timestamp)
        : type(type), amount(amount), timestamp(timestamp) {}
};

#endif
