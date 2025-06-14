# 🛒 Stock Order Book Simulator (C++)

This is a simple stock market simulator that matches buy and sell orders, just like in a real trading platform (kind of like Zerodha or Robinhood). I built this as a fun way to apply DSA concepts — especially **heaps (priority queues)** — in something that actually feels real.

---

## 💡 What It Does

- You can place buy or sell orders for a stock at a certain price.
- The simulator tries to match them automatically:
  - **Buyers want to buy at the lowest possible price.**
  - **Sellers want to sell at the highest price they can get.**
- If a buy and sell price match (or cross), a trade happens.
- It keeps an **order book** so you can see pending orders.

---

## 📚 Concepts I Used

- `priority_queue` from STL (for heaps)
- Custom comparators (to sort buy and sell orders differently)
- Structs and classes in C++
- Simple command-line interface (menu)

---

## 🛠️ How to Run

Make sure you're using a system with `g++` or any C++ compiler.

### Compile:
```bash
g++ stock_simulator.cpp -o stock
