#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

struct Stock {
    std::string symbol; // stock symbol
    double price; // price per stock
};

enum OrderType { BUY, SELL };

struct Order {
    int orderID; // unique identifier, number of order
    std::string accountID; // name of user
    OrderType type; // BUY or SELL
    std::string symbol; // stock symbol
    int quantity; // number of stocks
    double price; // price per stock

    // Constructor
    Order(std::string accountID, OrderType type, std::string symbol, int quantity, double price) : accountID(accountID), type(type), symbol(symbol), quantity(quantity), price(price) {
        static int nextID = 0;
        orderID = nextID++;
    }
};

class Account {
private:
    std::string accountID; // name of user, assume unique
    double balance;
    std::unordered_map<std::string, int> holdings; // map of owned stocks, Symbol -> Quantity mapping
    std::vector<Order> pendingOrders; // list of pending orders
public:
    // Constructor and Destructor
    Account(std::string accountID, double balance) : accountID(accountID), balance(balance) {};
    Account(std::string accountID, double balance, std::unordered_map<std::string, int> holdings) : accountID(accountID), balance(balance), holdings(holdings) {};

    // Functions
    // Add to balance
    void deposit(double amount) {
        balance += amount;
    }
    // Buy: subtract from balance, add to holdings
    void buy(Stock stock, int quantity) {
        balance -= stock.price * quantity;
        holdings[stock.symbol] += quantity;
    }
    // Sell: add to balance, subtract from holdings
    void sell(Stock stock, int quantity) {
        balance += stock.price * quantity;
        holdings[stock.symbol] -= quantity;
    }
    // Add order to pendingOrders
    void addOrder(Order order) {
        pendingOrders.push_back(order);
    }
    // Remove order from pendingOrders
    void removeOrder(int orderID) {
        for (int i = 0; i < pendingOrders.size(); i++) {
            if (pendingOrders[i].orderID == orderID) {
                pendingOrders.erase(pendingOrders.begin() + i);
                break;
            }
        }
    }
    // Get balance
    double getBalance() const {
        return balance;
    }
    // Get quantity of a stock
    int getHoldings(std::string symbol) const {
        return holdings.at(symbol);
    }
    // Print account details
    void printAccount() const {
        std::cout << "Account ID: " << accountID << std::endl;
        std::cout << "Balance: " << balance << std::endl;
        std::cout << "Holdings: " << std::endl;
        for (auto& holding : holdings) {
            std::cout << "- " << holding.first << ": " << holding.second << std::endl;
        }
        std::cout << "Pending Orders: " << std::endl;
        for (auto& order : pendingOrders) {
            std::cout << "Order ID: " << order.orderID << std::endl;
            std::cout << "Type: " << (order.type == BUY ? "BUY" : "SELL") << std::endl;
            std::cout << "Symbol: " << order.symbol << std::endl;
            std::cout << "Quantity: " << order.quantity << std::endl;
            std::cout << "Price: " << order.price << std::endl;
            std::cout << std::endl;
        }
    }
};

#endif // ACCOUNT_H