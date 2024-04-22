#ifndef ORDERBOOK_H
#define ORDERBOOK_H

#include <queue>
#include "Account.hpp"

// Define greater operator for Order
bool operator>(const Order& a, const Order& b) {
    return a.price > b.price;
}
bool operator<(const Order& a, const Order& b) {
    return a.price < b.price;
}

class OrderBook {
private:
    std::unordered_map<std::string, Account> accounts; // accountID -> Account mapping
    std::unordered_map<std::string, std::priority_queue<Order, std::vector<Order>, std::greater<Order>>> sellOrders; // Symbol -> Min heap of sell orders
    std::unordered_map<std::string, std::priority_queue<Order, std::vector<Order>, std::less<Order>>> buyOrders; // Symbol -> max heap of buy orders
public:
    // Constructor
    OrderBook() {};
    // Functions
    void addOrder(Order order); // add order to buyOrders or sellOrders
    void removeOrder(int orderID); // remove order from buyOrders or sellOrders
    void executeOrder(); // match buy and sell orders
    void printOrderBook() const; // print all orders in the order book
};

#endif // ORDERBOOK_H