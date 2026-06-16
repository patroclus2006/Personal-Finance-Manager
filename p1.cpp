#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>
using namespace std;

// -------------------- Transaction Class --------------------
// Encapsulation: data is private
class Transaction {
private:
    string type;
    double amount;

public:
    Transaction() : type("Unknown"), amount(0) {}
    Transaction(const string& t, double a) : type(t), amount(a) {}
    ~Transaction() {}

    string getType() const { return type; }
    double getAmount() const { return amount; }

    void display() const {
        cout << " - " << type << ": " << amount << endl;
    }

    friend void printTransactionPrivate(const Transaction& t);
};

// Friend function: can access private members
void printTransactionPrivate(const Transaction& t) {
    cout << "[Friend] Private data -> Type: " << t.type
         << ", Amount: " << t.amount << endl;
}

// -------------------- Account Class --------------------
// Composition: Account has vector<Transaction>
class Account {
private:
    double income;
    vector<Transaction> expenses;
    double savingsGoal;

public:
    Account() : income(0), savingsGoal(0) {}
    Account(double inc) : income(inc), savingsGoal(0) {}
    ~Account() {}

    void setIncome(double inc) { income = inc; }
    double getIncome() const { return income; }

    void setSavingsGoal(double goal) { savingsGoal = goal; }
    double getSavingsGoal() const { return savingsGoal; }

    void addExpense(const string& type, double amount) {
        expenses.emplace_back(type, amount);

        ofstream file("expenses.txt", ios::app);
        if (file) {
            file << type << "," << amount << "\n";
        }
    }

    void loadExpenses() {
        ifstream file("expenses.txt");
        if (!file) return;

        expenses.clear();

        string type;
        double amount;

        while (getline(file, type, ',')) {
            if (!(file >> amount)) break;
            file.ignore(numeric_limits<streamsize>::max(), '\n');
            expenses.emplace_back(type, amount);
        }
    }

    void showExpenses() const {
        if (expenses.empty()) {
            cout << "No expenses recorded yet.\n";
            return;
        }

        cout << "Recorded expenses:\n";
        for (const auto& e : expenses) {
            e.display();
        }
    }

    double totalExpenses() const {
        double sum = 0;
        for (const auto& e : expenses) {
            sum += e.getAmount();
        }
        return sum;
    }

    double monthlyBudget(double percent) const {
        return income * percent;
    }

    double netWorth() const {
        return income - totalExpenses();
    }

    friend void showPrivateSummary(const Account& acc);
};

// Friend function for account
void showPrivateSummary(const Account& acc) {
    cout << "[Friend] Income: " << acc.income << endl;
    cout << "[Friend] Expenses total: " << acc.totalExpenses() << endl;
}

// -------------------- Abstraction --------------------
// Abstract class
class Report {
public:
    virtual void generate(const Account& acc) const = 0;
    virtual ~Report() {}
};

// -------------------- Inheritance + Polymorphism --------------------
class SummaryReport : public Report {
public:
    void generate(const Account& acc) const override {
        cout << "\n--- Summary Report ---\n";
        cout << "Income: " << acc.getIncome() << endl;
        cout << "Total Expenses: " << acc.totalExpenses() << endl;
        cout << "Net Worth: " << acc.netWorth() << endl;
    }
};

class DetailedReport : public Report {
public:
    void generate(const Account& acc) const override {
        cout << "\n--- Detailed Report ---\n";
        cout << "Income: " << acc.getIncome() << endl;
        acc.showExpenses();
        cout << "Total Expenses: " << acc.totalExpenses() << endl;
        cout << "Net Worth: " << acc.netWorth() << endl;
    }
};

// -------------------- Analysis --------------------
void showAnalysis(const Account& acc) {
    cout << "\n--- Analysis / Tahlil ---\n";

    double income = acc.getIncome();
    dou

ble expense = acc.totalExpenses();
    double remain = income - expense;

    cout << "Income: " << income << endl;
    cout << "Expenses: " << expense << endl;
    cout << "Remaining money: " << remain << endl;

    if (income > 0) {
        cout << "Spending ratio: " << fixed << setprecision(2)
             << (expense / income) * 100 << "%\n";
    }

    showPrivateSummary(acc);

    if (remain < 0) {
        cout << "Warning: you are overspending.\n";
    } else {
        cout << "Your budget is under control.\n";
    }
}

int main() {
    int income;
    char income_form;
    int result = 0;
    int registery = 2585;

    cout << "Welcome to my Personal Finance Manager\n";
    cout << "please enter your registery code\n";
    cin >> registery;

    if (registery != 2585) {
        cout << "wrong code";
        return 0;
    } else {
        cout << "correct welcome\n";
    }

    cout << "Please enter your income so we can start\n";
    cout << "(Your income can be monthly, weekly or daily)\n";
    cin >> income;

    cout << "If your income is monthly enter 'M'\n";
    cout << "if weekly enter 'W'\n";
    cout << "if daily enter 'D'\n";
    cin >> income_form;

    if (income_form == 'D' || income_form == 'd') {
        result = income * 30;
    }
    else if (income_form == 'W' || income_form == 'w') {
        result = income * 4;
    }
    else if (income_form == 'M' || income_form == 'm') {
        result = income;
    }
    else {
        cout << "Invalid type!\n";
        return 0;
    }

    cout << "Your monthly income is " << result << endl;

    Account account(result);
    account.loadExpenses();

    char ability;

    while (true) {
        cout << "\tMain Menu\t\n";
        cout << "Budgeting -> B\n";
        cout << "Expense Tracking -> E\n";
        cout << "Savings Goals -> S\n";
        cout << "Net Worth -> N\n";
        cout << "Analysis -> A\n";
        cout << "Reporting -> R\n";
        cout << "Exit -> 0\n";
        cout << "Enter your choice: ";
        cin >> ability;

        if (ability == '0') {
            cout << "Goodbye!\n";
            break;
        }

        if (ability == 'B' || ability == 'b') {
            int budget_risk;
            double budget = 0;

            cout << "Choose budgeting type:\n";
            cout << "High risk (90%) -> 90\n";
            cout << "Medium risk (75%) -> 75\n";
            cout << "Low risk (60%) -> 60\n";
            cout << "Enter choice: ";
            cin >> budget_risk;

            if (budget_risk == 90) {
                budget = account.monthlyBudget(0.9);
            }
            else if (budget_risk == 75) {
                budget = account.monthlyBudget(0.75);
            }
            else if (budget_risk == 60) {
                budget = account.monthlyBudget(0.6);
            }
            else {
                cout << "Invalid option!\n";
                continue;
            }

            cout << "Your customized budget is " << budget << endl;
            cout << "You can spend up to this amount safely without seeing '0' in your bank account.\n";
        }

        else if (ability == 'E' || ability == 'e') {
            cout << "welcome to Expense Tracking section\n";
            cout << "please type your expense_type and add how much you spend on it\n";

            string expense_type;
            double expense;

            cout << "you've spent: ";
            cin >> expense;

            cout << "on: ";
            cin >> expense_type;

            account.addExpense(expense_type, expense);

            cout << "Expense saved successfully.\n";
        }

        else if (ability == 'S' || ability == 's') {
            cout << "Savings Goals section\n";
            double goal;
            cout << "Enter your savings goal: ";
            cin >> goal;
            account.setSavingsGoal(goal);

            cout << "Goal saved: " << account.getSavingsGoal() << endl;
            cout << "Money left after expenses: " << account.netWorth() << endl;
        }

        else if (ability == 'N' || ability == 'n') {

cout << "Net Worth section\n";
            cout << "Your net worth is: " << account.netWorth() << endl;
        }

        else if (ability == 'A' || ability == 'a') {
            showAnalysis(account);
        }

        else if (ability == 'R' || ability == 'r') {
            cout << "Reporting section\n";

            int type;
            cout << "Choose report type:\n";
            cout << "1 -> Summary Report\n";
            cout << "2 -> Detailed Report\n";
            cout << "Enter choice: ";
            cin >> type;

            Report* report = nullptr;

            if (type == 1) {
                report = new SummaryReport();
            }
            else if (type == 2) {
                report = new DetailedReport();
            }
            else {
                cout << "Invalid report type!\n";
                continue;
            }

            report->generate(account);
            delete report;
        }

        else {
            cout << "Invalid choice!\n";
        }
    }

    return 0;
}
