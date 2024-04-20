#include <iostream>
#include <stack>
#include <ctime>
#include <vector>
// predefine type
using Price = std::int32_t;
using Quantity = std::uint32_t;
using OrderId = std::uint64_t;
using UserId = std::uint64_t;

using OrderIdList = std::vector<OrderId>;
enum class OrderType
{
        GoodTillCancel,
        FillAndKill,
        GoodForDay,
        Partial,
        Market,
        Limit
};
enum class Side
{
        buy,
        sell
};

struct Account
{
        UserId userId;
        int Balance;
        Quantity stockQuantity;
        std::vector<Order> orders;
        std::vector<Order> matchedOrders;
        std::vector<Order> cancelledOrders;
        std::vector<Order> pendingOrders;
        std::vector<Order> completedOrders;
        std::vector<Order> partialOrders;
};
enum class OrderStatus
{
        Filled,
        Cancelled,
        Pending,
        Completed,
        Partial
};

struct Order
{
        OrderType type;
        Quantity quantity;
        Price price;
        Side side;
        OrderId orderId;
        UserId userId;
        time_t time;
        OrderStatus status;
        Order(OrderType type, Quantity quantity, Price price, Side side, OrderId orderId, UserId userId, time_t time, OrderStatus status) : type(type), quantity(quantity), price(price), side(side), orderId(orderId), userId(userId), time(time), status(status) {}
};

class OrderBook
{
private:
        // for now, store bid & sell info, might need to set up an API to enhance security
        std::stack<Order> buyOrders;
        std::stack<Order> sellOrders;
        std::vector<Account> accounts;
        std::vector<OrderIdList> orderIds;
        std::vector<Order> orders;
        std::vector<Order> matchedOrders;
        std::vector<Order> cancelledOrders;
        std::vector<Order> pendingOrders;
        std::vector<Order> completedOrders;
        std::vector<Order> partialOrders;

public:
        void CancelOrder()
        {
        }
        void createOrder()
        {
        }

        void GoodForDay()
        {
                // auto cancel order when one day has elapsed
        }
        void MatchOrders()
        {
                // matching seller with buyer
        }
        OrderBook();
};
