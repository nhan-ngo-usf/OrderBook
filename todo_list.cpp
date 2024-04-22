/*
*** STRUCT ***
- Create a struct Stock with the following attributes:
    - string symbol
    - double price
- enum OrderType { BUY, SELL }
- Create a struct Order with the following attributes:
    - int orderID // unique identifier, no. of order
        + create a static variable nextID -> constructor Order(nextID++, ...)
    - string accountID // name of user
    - OrderType type
    - string symbol
    - int quantity
    - double price

*** CLASS ***
ACCOUNT:
- Attributes:
    - string accountID // unique identifier, name of user
    - double balance
    - unordered_map<string, int> holdings // map of owned stocks, Symbol -> Quantity mapping
    - vector<Order> pendingOrders // list of pending orders
- Functions:
    - constructor Account(string name, double balance)
    - void deposit(double amount) // add to balance

    - void buy(Stock stock, int quantity) // subtract from balance, add to holdings
    - void sell(Stock stock, int quantity) // add to balance, subtract from holdings

    - void addOrder(Order order) // add order to pendingOrders
    - void removeOrder(int orderID) // remove order from pendingOrders

    - double getBalance() const
    - int getHoldings(string symbol) const // return quantity of a stock
    - void printAccount() const // print account details

!!! NOTE: 
- Store all accounts: unordered_map<string, Account> accounts // accountID -> Account mapping
*/

/*
ORDER BOOK:
- Attributes:
    - unordered_map<string, priority_queue<Order, vector<Order>, greater<Order>>> sellOrders // Symbol -> Min heap of sell orders
    - unordered_map<string, queue<Order>> buyOrders // Symbol -> queue of buy orders
- Functions:
    - void addOrder(Order order) // add order to buyOrders or sellOrders
    - void cancelOrder(int orderID) // remove order from buyOrders or sellOrders
    - void executeOrder() // match buy and sell orders

    - void printOrderBook() const // print all orders in the order book
*/

/*
*** MAIN ***
- Create account: Account("Alice", 1000), Account("Bob", 500), Account("Charlie", 2000)
- Create an order book
- Add a buy order for 5 AAPL stocks at $150
- Add a sell order for 3 AAPL stocks at $150
- Execute the order
- Print the account details and order book
- Add a buy order for 2 AAPL stocks at $160
- Add a sell order for 1 AAPL stock at $160
- Execute the order
- Print the account details and order book
- Cancel the remaining orders
- Print the account details and order book
*/