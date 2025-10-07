#include "BankAccount.h"
#include "CheckingAccount.h"
#include "SavingsAccount.h"
#include <ctime>
#include <iomanip>

// Helper function to get current timestamp
string getCurrentTime() {
    time_t now = time(nullptr);
    tm* localTime = localtime(&now);
    char buffer[80];
    strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", localTime);
    return string(buffer);
}

// ---------------------- BankAccount ----------------------
BankAccount::BankAccount() : accountNumber(""), accountHolderName(""), balance(new double(0.0)) {}

BankAccount::BankAccount(const string& accNum, const string& holder, double initialBalance)
    : accountNumber(accNum), accountHolderName(holder), balance(new double(initialBalance)) {}

BankAccount::~BankAccount() { delete balance; }

void BankAccount::deposit(double amount) {
    if (amount > 0) {
        *balance += amount;
        transactionHistory.emplace_back("Deposit", amount, getCurrentTime());
    } else {
        cout << "Deposit must be positive.\n";
    }
}

void BankAccount::withdraw(double amount) {
    if (amount <= 0) cout << "Withdrawal must be positive.\n";
    else if (amount > *balance) cout << "Insufficient funds.\n";
    else {
        *balance -= amount;
        transactionHistory.emplace_back("Withdrawal", amount, getCurrentTime());
    }
}

double BankAccount::getBalance() const { return *balance; }
string BankAccount::getAccountHolderName() const { return accountHolderName; }
string BankAccount::getAccountNumber() const { return accountNumber; }

void BankAccount::printAccount() const {
    cout << "Account Number: " << accountNumber
         << "\nAccount Holder: " << accountHolderName
         << "\nBalance: $" << *balance << "\n";
}

void BankAccount::printHistory() const {
    cout << "\n--- Transaction History for " << accountHolderName << " ---\n";
    if (transactionHistory.empty()) {
        cout << "No transactions recorded.\n";
        return;
    }
    for (const auto& t : transactionHistory) {
        cout << left << setw(12) << t.type << "$" << setw(10) << t.amount
             << " at " << t.timestamp << "\n";
    }
}

// ---------------------- CheckingAccount ----------------------
CheckingAccount::CheckingAccount(const string& accNum, const string& holder,
                                 double initialBalance, double fee)
    : BankAccount(accNum, holder, initialBalance), transactionFee(fee) {}

void CheckingAccount::withdraw(double amount) {
    double total = amount + transactionFee;
    if (total > getBalance()) {
        cout << "Insufficient funds including transaction fee.\n";
    } else {
        BankAccount::withdraw(total);
        transactionHistory.emplace_back("Transaction Fee", transactionFee, "N/A");
    }
}

void CheckingAccount::printAccount() const {
    BankAccount::printAccount();
    cout << "Transaction Fee: $" << transactionFee << "\n";
}

// ---------------------- SavingsAccount ----------------------
SavingsAccount::SavingsAccount(const string& accNum, const string& holder,
                               double initialBalance, double rate)
    : BankAccount(accNum, holder, initialBalance), interestRate(rate) {}

void SavingsAccount::calculateInterest() {
    double interest = *balance * interestRate;
    *balance += interest;
    transactionHistory.emplace_back("Interest", interest, "N/A");
}

void SavingsAccount::printAccount() const {
    BankAccount::printAccount();
    cout << "Interest Rate: " << interestRate * 100 << "%\n";
}
