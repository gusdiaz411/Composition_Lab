#include <iostream>
#include <vector>
#include <memory>
#include <limits>
#include "BankAccount.h"
#include "CheckingAccount.h"
#include "SavingsAccount.h"

using namespace std;

int main() {
    vector<unique_ptr<BankAccount>> accounts;
    int choice;

    do {
        cout << "\n--- Bank Account Menu ---\n";
        cout << "1. Create Checking Account\n";
        cout << "2. Create Savings Account\n";
        cout << "3. Deposit\n";
        cout << "4. Withdraw\n";
        cout << "5. Calculate Interest (Savings Only)\n";
        cout << "6. Print Account\n";
        cout << "7. Print Transaction History\n";
        cout << "8. Exit\n";
        cout << "Enter choice: ";

        while (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Enter a number (1-8): ";
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1: {
                string accNum, holder;
                double balance, fee;
                cout << "Account Number: ";
                getline(cin, accNum);
                cout << "Account Holder Name: ";
                getline(cin, holder);
                cout << "Initial Balance: ";
                cin >> balance;
                cout << "Transaction Fee: ";
                cin >> fee;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                accounts.push_back(make_unique<CheckingAccount>(accNum, holder, balance, fee));
                cout << "Checking account created successfully!\n";
                break;
            }
            case 2: {
                string accNum, holder;
                double balance, rate;
                cout << "Account Number: ";
                getline(cin, accNum);
                cout << "Account Holder Name: ";
                getline(cin, holder);
                cout << "Initial Balance: ";
                cin >> balance;
                cout << "Interest Rate (e.g., 0.05 for 5%): ";
                cin >> rate;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                accounts.push_back(make_unique<SavingsAccount>(accNum, holder, balance, rate));
                cout << "Savings account created successfully!\n";
                break;
            }
            case 3: {
                if (accounts.empty()) {
                    cout << "No accounts available.\n";
                    break;
                }
                int index;
                double amount;
                cout << "Enter account number (1-" << accounts.size() << "): ";
                cin >> index;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                if (index < 1 || index > (int)accounts.size()) {
                    cout << "Invalid account number.\n";
                    break;
                }

                cout << "Enter deposit amount: ";
                cin >> amount;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                accounts[index - 1]->deposit(amount);
                cout << "Deposit successful.\n";
                break;
            }
            case 4: {
                if (accounts.empty()) {
                    cout << "No accounts available.\n";
                    break;
                }
                int index;
                double amount;
                cout << "Enter account number (1-" << accounts.size() << "): ";
                cin >> index;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                if (index < 1 || index > (int)accounts.size()) {
                    cout << "Invalid account number.\n";
                    break;
                }

                cout << "Enter withdrawal amount: ";
                cin >> amount;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                accounts[index - 1]->withdraw(amount);
                break;
            }
            case 5: {
                if (accounts.empty()) {
                    cout << "No accounts available.\n";
                    break;
                }

                for (size_t i = 0; i < accounts.size(); ++i) {
                    SavingsAccount* savings = dynamic_cast<SavingsAccount*>(accounts[i].get());
                    if (savings) {
                        savings->calculateInterest();
                        cout << "Interest calculated for account #" << i + 1 << "\n";
                    }
                }
                break;
            }
            case 6: {
                if (accounts.empty()) {
                    cout << "No accounts available.\n";
                    break;
                }
                int index;
                cout << "Enter account number (1-" << accounts.size() << "): ";
                cin >> index;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                if (index < 1 || index > (int)accounts.size()) {
                    cout << "Invalid account number.\n";
                    break;
                }

                accounts[index - 1]->printAccount();
                break;
            }
            case 7: {
                if (accounts.empty()) {
                    cout << "No accounts available.\n";
                    break;
                }
                int index;
                cout << "Enter account number (1-" << accounts.size() << "): ";
                cin >> index;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                if (index < 1 || index > (int)accounts.size()) {
                    cout << "Invalid account number.\n";
                    break;
                }

                accounts[index - 1]->printHistory();
                break;
            }
            case 8:
                cout << "Exiting program. Goodbye!\n";
                break;

            default:
                cout << "Invalid choice. Please enter 1-8.\n";
        }

    } while (choice != 8);

    return 0;
}
