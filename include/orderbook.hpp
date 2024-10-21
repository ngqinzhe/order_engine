#ifndef ORDERBOOK_HPP
#define ORDERBOOK_HPP
#pragma once
#include "limit.hpp"
#include "order.hpp"
#include "trade.hpp"
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

class Orderbook {
private:
  // order map to store orderId -> orders
  using OrderMap =
      std::unordered_map<std::string, std::list<OrderPointer>::const_iterator>;
  OrderMap orderMap_;

  using TimestampOrderMap =
      std::unordered_map<std::string, std::list<OrderPointer>::const_iterator>;
  TimestampOrderMap timestampOrderMap_;

  // bid / ask limit levels
  Limit<std::greater<double>> bid_;
  Limit<std::less<double>> ask_;
  std::string instrument_;

  std::vector<TradeInfo> matchOrders() {
    std::vector<TradeInfo> trades;
    for (;;) {
      // no order on each side -> no match
      if (ask_.empty() || bid_.empty())
        break;

      if (bid_.bestPrice() < ask_.bestPrice())
        break;
      // std::cout << "stuck here" << "\n";
      auto bestBid = bid_.top();
      auto bestAsk = ask_.top();
      // if buy price does not match up to sell price -> no match
      while (!bestBid->empty() && !bestAsk->empty()) {
        auto bid = bestBid->front();
        auto ask = bestAsk->front();
        // std::cout << "stuck cuz of bid: " << bid->getOrderId() << " and ask:
        // " << ask->getOrderId() << "\n";
        double tradeQuantity =
            std::min(bid->getRemainingQuantity(), ask->getRemainingQuantity());
        double tradePrice = bid->getPrice();

        // traded
        trades.emplace_back(TradeInfo{instrument_, ask->getOrderId(),
                                      bid->getOrderId(), tradeQuantity,
                                      tradePrice});

        // deduct trade quantity from order
        bid->fill(tradeQuantity);
        ask->fill(tradeQuantity);
        // remove from orderbook if order quantity is filled
        if (bid->filled())
          removeOrder(bid->getOrderId());
        if (ask->filled())
          removeOrder(ask->getOrderId());

        // std::cout << "bidsize: " << bestBid->size() << " asksize: " <<
        // bestAsk->size() << "\n";
      }
    }
    return trades;
  }

public:
  Orderbook(std::string instrument) : instrument_(instrument) {};
  Orderbook(const Orderbook&) = default;
  Orderbook& operator=(const Orderbook&) = default;
  ~Orderbook() = default;

  std::vector<TradeInfo> insertOrder(const Order &order) {
    std::list<OrderPointer>::const_iterator it;
    std::list<OrderPointer>::const_iterator timestampIter;
    if (order.isBuy()) {
      bid_.insert(order);
      it = bid_.getLatestOrder(order.getPrice());
      timestampIter = bid_.getLatestOrderByTime();
    } else {
      ask_.insert(order);
      it = ask_.getLatestOrder(order.getPrice());
      timestampIter = ask_.getLatestOrderByTime();
    }
    orderMap_[order.getOrderId()] = it;
    timestampOrderMap_[order.getOrderId()] = timestampIter;
    return matchOrders();
  }

  void removeOrder(std::string orderId) {
    if (orderMap_.find(orderId) == orderMap_.end())
      return;
    auto orderIter = orderMap_[orderId];
    auto timestampIter = timestampOrderMap_[orderId];
    if (orderIter->get()->isBuy()) {
      bid_.remove(orderIter->get()->getPrice(), orderIter, timestampIter);
    } else {
      ask_.remove(orderIter->get()->getPrice(), orderIter, timestampIter);
    }
    orderMap_.erase(orderId);
    timestampOrderMap_.erase(orderId);
  }

  friend std::ostream &operator<<(std::ostream &os,
                                  const Orderbook &orderbook) {
    os << orderbook.ask_ << orderbook.bid_;
    return os;
  }
};

#endif