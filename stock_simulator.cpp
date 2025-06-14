#include <iostream>
#include <queue>
#include <vector>
#include <iomanip>

using namespace std;

struct Order {
    int id;
    string type;   
    int quantity;
    double price;

    Order(int i, string t, int q, double p) : id(i), type(t), quantity(q), price(p) {}
};

struct CompareBuy {
    bool operator()(Order &a, Order &b) {
        return a.price < b.price;
    }
};

struct CompareSell {
    bool operator()(Order &a, Order &b) {
        return a.price > b.price;  
    }
};

class OrderBook {
    int orderId = 1;

    priority_queue<Order, vector<Order>, CompareBuy> buyHeap;
    priority_queue<Order, vector<Order>, CompareSell> sellHeap;

public:
    void placeOrder(string type, int qty, double price) {
        Order order(orderId++, type, qty, price);
        cout << "\n[+] Placing " << type << " order: " << qty << " @ ₹" << price << "\n";

        if (type == "buy") {
            matchOrder(order, sellHeap, false);
            if (order.quantity > 0) buyHeap.push(order);
        } else {
            matchOrder(order, buyHeap, true);
            if (order.quantity > 0) sellHeap.push(order);
        }
    }

    void matchOrder(Order &incoming, auto &heap, bool isBuy) {
        while (!heap.empty() && incoming.quantity > 0) {
            Order top = heap.top();

            bool priceMatch = (isBuy && incoming.price <= top.price)
                           || (!isBuy && incoming.price >= top.price);
            if (!priceMatch) break;

            int tradeQty = min(incoming.quantity, top.quantity);
            double tradePrice = top.price;

            cout << " Trade executed: " << tradeQty << " @ ₹" << tradePrice << "\n";

            incoming.quantity -= tradeQty;
            top.quantity -= tradeQty;
            heap.pop();

            if (top.quantity > 0) heap.push(top); 
        }
    }

    void showOrders() {
        cout << "\n=====  Order Book =====\n";

        auto tempBuy = buyHeap;
        auto tempSell = sellHeap;

        cout << "\n Sell Orders:\n";
        while (!tempSell.empty()) {
            Order o = tempSell.top(); tempSell.pop();
            cout << o.quantity << " @ ₹" << fixed << setprecision(2) << o.price << "\n";
        }

        cout << "\n📥 Buy Orders:\n";
        while (!tempBuy.empty()) {
            Order o = tempBuy.top(); tempBuy.pop();
            cout << o.quantity << " @ ₹" << fixed << setprecision(2) << o.price << "\n";
        }

        cout << "=============================\n";
    }
};

int main() {
    OrderBook ob;
    int choice;

    while (true) {
        cout << "\n Stock Order Book Menu:\n";
        cout << "1. Place Buy Order\n";
        cout << "2. Place Sell Order\n";
        cout << "3. View Order Book\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1 || choice == 2) {
            int qty;
            double price;
            cout << "Enter quantity and price: ";
            cin >> qty >> price;
            string type = (choice == 1) ? "buy" : "sell";
            ob.placeOrder(type, qty, price);
        } else if (choice == 3) {
            ob.showOrders();
        } else if (choice == 4) {
            cout << "Exiting... Goodbye!\n";
            break;
        } else {
            cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}
