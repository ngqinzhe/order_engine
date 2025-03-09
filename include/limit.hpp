#ifndef LIMIT_HPP
#define LIMIT_HPP
#pragma once
#include "order.hpp"
#include <iostream>
#include <list>
#include <map>
#include <memory>

template <typename Cmp> class Limit {
private:
  // for price/time priority of orders
  std::map<double, std::shared_ptr<std::list<OrderPointer>>, Cmp> container_;
  // for timestamp of arrival of orders
  std::list<OrderPointer> timestampContainer_;

public:
  Limit() {}
  Limit(const Limit &) = default;
  Limit &operator=(const Limit &) = default;
  ~Limit() = default;

  void insert(const Order &order) {
    if (container_[order.getPrice()] == nullptr)
      container_[order.getPrice()] =
          std::make_shared<std::list<OrderPointer>>();
    auto orderPtr = std::make_shared<Order>(order);
    container_[order.getPrice()]->emplace_back(orderPtr);
    timestampContainer_.emplace_back(orderPtr);
  }

  std::list<OrderPointer>::iterator
  getLatestOrder(double price) {
    auto end = container_.at(price)->end();
    --end;
    return end;
  }

  std::list<OrderPointer>::iterator getLatestOrderByTime() {
    std::list<OrderPointer>::iterator end = timestampContainer_.end();
    --end;
    return end;
  }

  double bestPrice() const { return container_.begin()->first; }

  std::shared_ptr<std::list<OrderPointer>> top() const {
    return container_.begin()->second;
  }

  bool empty() const { return container_.empty(); }

  void remove(double price, std::list<OrderPointer>::iterator it,
              std::list<OrderPointer>::iterator timestampIter) {
    container_[price]->erase(it);
    if (container_[price]->empty())
      container_.erase(price);
    timestampContainer_.erase(timestampIter);
  }

  friend std::ostream &operator<<(std::ostream &os, const Limit &limit) {
    for (auto it = limit.timestampContainer_.begin();
         it != limit.timestampContainer_.end(); ++it) {
      os << it->get()->getOrderId() << " " << it->get()->getSide() << " "
         << it->get()->getInstrument() << " "
         << it->get()->getRemainingQuantity() << " " << it->get()->getPrice()
         << "\n";
    }
    return os;
  }
};

#endif