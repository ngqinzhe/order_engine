#ifndef ORDER_HPP
#define ORDER_HPP
#pragma once
#include <ctime>
#include <memory>
#include <string>

class Order {
private:
  std::string orderId_;
  // isBuy == true
  bool side_;
  std::string instrument_;
  double initialQuantity_;
  double filledQuantity_;
  double price_;
  time_t timestamp_;

public:
  Order(std::string orderId, std::string side, std::string instrument,
        double quantity, double price)
      : orderId_(orderId), instrument_(instrument), initialQuantity_(quantity),
        filledQuantity_(0), price_(price) {
    side_ = side == "BUY";
    timestamp_ = std::time(0);
  }
  Order(const Order&) = default;
  Order& operator=(const Order&) = default;
  ~Order() = default;
  // getters
  std::string getOrderId() const { return orderId_; }
  bool isBuy() const { return side_; }
  std::string getSide() const { return isBuy() ? "BUY" : "SELL"; }
  std::string getInstrument() const { return instrument_; }
  double getInitialQuantity() const { return initialQuantity_; }
  double getRemainingQuantity() const {
    return initialQuantity_ - filledQuantity_;
  }
  double getPrice() const { return price_; }
  bool filled() const { return filledQuantity_ == initialQuantity_; }

  // modifiers
  void fill(double quantity) { filledQuantity_ += quantity; }
};

using OrderPointer = std::shared_ptr<Order>;

#endif