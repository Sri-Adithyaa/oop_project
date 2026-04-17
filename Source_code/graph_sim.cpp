#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

#define GREEN "\033[32m"
#define RED   "\033[31m"
#define RESET "\033[0m"

struct Transaction {
    string company;
    double price;
};

int main() 
{
    ifstream file("transaction.txt");
    vector<Transaction> data;
    string line;

    //  Read file
    while (getline(file, line)) {
        stringstream ss(line);
        Transaction t;
        string temp;

        getline(ss, t.company, '|'); 
        getline(ss, temp, '|');      
        getline(ss, temp, '|');      
        getline(ss, temp, '|');      
        getline(ss, temp, '|');      

        t.price = stod(temp);
        data.push_back(t);
    }

    string companyInput;
    cout << "Enter company Symbol: ";
    cin >> companyInput;

    // Filter prices
    vector<double> prices;
    for (auto &t : data) {
        if (t.company == companyInput)
            prices.push_back(t.price);
    }

    if (prices.empty()) {
        cout << "No data found\n";
        return 0;
    }

    double maxP = *max_element(prices.begin(), prices.end());
    double minP = *min_element(prices.begin(), prices.end());

    int height = 10;

    cout << "\n" << companyInput << " Price Trend\n\n";

    // Draw graph
    for (int row = height; row >= 0; row--) {
        double level = minP + (maxP - minP) * row / height;

        cout << setw(6) << fixed << setprecision(2) << level << " | ";

        for (int i = 0; i < prices.size(); i++) {
            if (abs(prices[i] - level) < (maxP - minP)/height/2) {
                
                if (i == 0) {
                    cout << " *  "; // first point no color
                } else if (prices[i] > prices[i-1]) {
                    cout << GREEN << " * " << RESET;
                } else if (prices[i] < prices[i-1]) {
                    cout << RED << " * " << RESET;
                } else {
                    cout << " * ";
                }

            } else {
                cout << "    ";
            }
        }
        cout << "\n";
    }

    // X-axis
    cout << "       ";
    for (int i = 0; i < prices.size(); i++)
        cout << "----";
    cout << "\n       ";

    for (int i = 0; i < prices.size(); i++)
        cout << "T" << i+1 << "  ";
    cout<<endl;
    string ch;
    cout<<"Press Enter to continue...";
    cin.ignore();
    cin.ignore();
    cin.get();
}
