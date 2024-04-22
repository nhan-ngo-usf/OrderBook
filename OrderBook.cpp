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
    for (auto& [symbol, buyOrder] : buyOrders) {
        std::priority_queue<Order, std::vector<Order>, std::less<Order>> temp; // Store orders that are not to be removed
        while (!buyOrder.empty()) {
            Order order = buyOrder.top();
            buyOrder.pop();
            if (order.orderID != orderID) {
                temp.push(order);
            } else {
                // Remove order from account's pending orders
                accounts[order.accountID].removeOrder(orderID);
                std::cout << "Order " << orderID << " removed from " << order.accountID << "'s account." << std::endl;
                return;
            }
        }
        buyOrder = temp;
    }
    // Find orderID in sellOrders
    for (auto& [symbol, sellOrder] : sellOrders) {
        std::priority_queue<Order, std::vector<Order>, std::greater<Order>> temp; // Store orders that are not to be removed
        while (!sellOrder.empty()) {
            Order order = sellOrder.top();
            sellOrder.pop();
            if (order.orderID != orderID) {
                temp.push(order);
            } else {
                // Remove order from account's pending orders
                accounts[order.accountID].removeOrder(orderID);
                std::cout << "Order " << orderID << " removed from " << order.accountID << "'s account." << std::endl;
                return;
            }
        }
        sellOrder = temp;
    }
}

// Match buy and sell orders
void OrderBook::executeOrder() {
    for (auto& [symbol, buyOrder] : buyOrders) {
        // Find available sell orders for symbol
        if (sellOrders.find(symbol) == sellOrders.end()) {
            std::cout << "No sell orders for " << symbol << ". Pending..." << std::endl;
            continue;
        }

        // Take the first one of each queue, compare, and execute if possible
        while (!buyOrder.empty() && !sellOrders[symbol].empty()) {
            Order buy = buyOrder.top();
            Order sell = sellOrders[symbol].top();
            
            if (buy.price >= sell.price) {
                int quantity = std::min(buy.quantity, sell.quantity); // Final quantity = minimum of buy and sell quantity
                double price = (buy.price + sell.price) / 2; // Final price = average of buy and sell price

                // Execute order
                accounts[buy.accountID].buy({symbol, price}, quantity);
                accounts[sell.accountID].sell({symbol, price}, quantity);
                buy.quantity -= quantity;
                sell.quantity -= quantity;
                std::cout << "Execute order " << buy.orderID << ": " << quantity << " " << symbol << " at " << price << " from " << sell.accountID << " to " << buy.accountID << std::endl;

                // Remove order if quantity is 0=
                if (buy.quantity == 0) {
                    buyOrder.pop();
                    accounts[buy.accountID].removeOrder(buy.orderID);
                }
                if (sell.quantity == 0) {
                    sellOrders[symbol].pop();
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
    for (auto& [symbol, sellOrder] : sellOrders) {
        std::cout << symbol << "\t";

        // Print sell orders
        std::priority_queue<Order, std::vector<Order>, std::greater<Order>> tempSell = sellOrder;
        while (!tempSell.empty()) {
            Order order = tempSell.top();
            tempSell.pop();
            std::cout << order.orderID << " " << order.quantity << " " << order.price << ", ";
        }
        std::cout << "\t";

        // Print buy orders
        std::priority_queue<Order, std::vector<Order>, std::less<Order>> tempBuy = buyOrders.at(symbol);
        while (!tempBuy.empty()) {
            Order order = tempBuy.top();
            tempBuy.pop();
            std::cout << order.orderID << " " << order.quantity << " " << order.price << ", ";
        }
        std::cout << std::endl;
    }
    // Print remaining in buyOrders
    for (auto& [symbol, buyOrder] : buyOrders) {
        if (sellOrders.find(symbol) == sellOrders.end()) {
            std::cout << symbol << "\t\t";
            // Print buy orders
            std::priority_queue<Order, std::vector<Order>, std::less<Order>> tempBuy = buyOrder;
            while (!tempBuy.empty()) {
                Order order = tempBuy.top();
                tempBuy.pop();
                std::cout << order.orderID << " " << order.quantity << " " << order.price << ", ";
            }
            std::cout << std::endl;
        }
    }
}