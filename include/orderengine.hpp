#ifndef ORDERENGINE_HPP
#define ORDERENGINE_HPP
#pragma once
#include "orderbook.hpp"
#include <iostream>
#include <map>
#include <string>

class OrderEngine {
private:
  std::map<std::string, std::shared_ptr<Orderbook>> orderbooks_;
  // trade logger
  TradeLogger tradeLogger_;

public:
  OrderEngine() {};
  OrderEngine(const OrderEngine &rhs) = default;
  ~OrderEngine() = default;

  void insertOrder(const Order &order) {
    if (orderbooks_.find(order.getInstrument()) == orderbooks_.end()) {
      orderbooks_[order.getInstrument()] =
          std::make_shared<Orderbook>(Orderbook(order.getInstrument()));
    }
    std::vector<TradeInfo> trades =
        orderbooks_[order.getInstrument()]->insertOrder(order);
    tradeLogger_.add(trades);
  }

  friend std::ostream &operator<<(std::ostream &os,
                                  const OrderEngine &orderEngine) {
    os << orderEngine.tradeLogger_ << "\n";
    for (auto &[_, orderbook] : orderEngine.orderbooks_) {
      os << *orderbook;
    }
    return os;
  }
};

#endif