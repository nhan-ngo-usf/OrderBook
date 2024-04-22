#include "OrderBook.hpp"

// Add order to buyOrders or sellOrders
void OrderBook::addOrder(Order order) {
    if (order.type == OrderType::BUY) {
        buyOrders[order.symbol].push(order);
    } else {
        sellOrders[order.symbol].push(order);
    }
    // Add order to account's pending orders
    accounts[order.accountID].addOrder(order);
    std::cout << "Order " << order.orderID << " added to " << order.accountID << "'s account." << std::endl;
}

// Remove order from buyOrders or sellOrders
void OrderBook::removeOrder(int orderID) {
    // Find orderID in buyOrders
    for (auto& pair : buyOrders) {
        std::priority_queue<Order, std::vector<Order>, std::less<Order>> temp; // Store orders that are not to be removed
        while (!pair.second.empty()) {
            Order order = pair.second.top();
            pair.second.pop();
            if (order.orderID != orderID) {
                temp.push(order);
            } else {
                // Remove order from account's pending orders
                accounts[order.accountID].removeOrder(orderID);
                std::cout << "Order " << orderID << " removed from " << order.accountID << "'s account." << std::endl;
                return;
            }
        }
        pair.second = temp;
    }
    // Find orderID in sellOrders
    for (auto& pair : sellOrders) {
        std::priority_queue<Order, std::vector<Order>, std::greater<Order>> temp; // Store orders that are not to be removed
        while (!pair.second.empty()) {
            Order order = pair.second.top();
            pair.second.pop();
            if (order.orderID != orderID) {
                temp.push(order);
            } else {
                // Remove order from account's pending orders
                accounts[order.accountID].removeOrder(orderID);
                std::cout << "Order " << orderID << " removed from " << order.accountID << "'s account." << std::endl;
                return;
            }
        }
        pair.second = temp;
    }
}

// Match buy and sell orders
void OrderBook::executeOrder() {
    for (auto& pair : buyOrders) {
        // Find available sell orders for symbol
        if (sellOrders.find(pair.first) == sellOrders.end()) {
            std::cout << "No sell orders for " << pair.first << ". Pending..." << std::endl;
            continue;
        }

        // Take the first one of each queue, compare, and execute if possible
        while (!pair.second.empty() && !sellOrders[pair.first].empty()) {
            Order buy = pair.second.top();
            Order sell = sellOrders[pair.first].top();
            
            if (buy.price >= sell.price) {
                int quantity = std::min(buy.quantity, sell.quantity); // Final quantity = minimum of buy and sell quantity
                double price = (buy.price + sell.price) / 2; // Final price = average of buy and sell price

                // Execute order
                accounts[buy.accountID].buy({pair.first, price}, quantity);
                accounts[sell.accountID].sell({pair.first, price}, quantity);
                buy.quantity -= quantity;
                sell.quantity -= quantity;
                std::cout << "Execute order " << buy.orderID << ": " << quantity << " " << pair.first << " at " << price << " from " << sell.accountID << " to " << buy.accountID << std::endl;

                // Remove order if quantity is 0=
                if (buy.quantity == 0) {
                    pair.second.pop();
                    accounts[buy.accountID].removeOrder(buy.orderID);
                }
                if (sell.quantity == 0) {
                    sellOrders[pair.first].pop();
                    accounts[sell.accountID].removeOrder(sell.orderID);
                }

            } else {
                break; // If the buy price is less than the sell price, no more orders can be executed
            }
        }
    }
}

// Print all orders in the order book
void OrderBook::printOrderBook() const {
    std::cout << "Symbol\tSell Orders\tBuy Orders" << std::endl;
    // Print a table with columns: Symbol, Sell Orders, Buy Orders
    // Print based on sellOrders first
    for (auto& pair : sellOrders) {
        std::cout << pair.first << "\t";

        // Print sell orders
        std::priority_queue<Order, std::vector<Order>, std::greater<Order>> tempSell = pair.second;
        while (!tempSell.empty()) {
            Order order = tempSell.top();
            tempSell.pop();
            std::cout << order.orderID << " " << order.quantity << " " << order.price << ", ";
        }
        std::cout << "\t";

        // Print buy orders
        std::priority_queue<Order, std::vector<Order>, std::less<Order>> tempBuy = buyOrders.at(pair.first);
        while (!tempBuy.empty()) {
            Order order = tempBuy.top();
            tempBuy.pop();
            std::cout << order.orderID << " " << order.quantity << " " << order.price << ", ";
        }
        std::cout << std::endl;
    }
    // Print remaining in buyOrders
    for (auto& pair : buyOrders) {
        if (sellOrders.find(pair.first) == sellOrders.end()) {
            std::cout << pair.first << "\t\t";
            // Print buy orders
            std::priority_queue<Order, std::vector<Order>, std::less<Order>> tempBuy = pair.second;
            while (!tempBuy.empty()) {
                Order order = tempBuy.top();
                tempBuy.pop();
                std::cout << order.orderID << " " << order.quantity << " " << order.price << ", ";
            }
            std::cout << std::endl;
        }
    }
}