#ifndef TRADE_HPP
#define TRADE_HPP
#pragma once
#include <iostream>
#include <string>
#include <vector>

struct TradeInfo {
  std::string instrument;
  std::string sellOrderId;
  std::string buyOrderId;
  double quantity;
  double price;
};

class TradeManager {
private:
  std::vector<TradeInfo> _trades;

public:
  TradeManager() {}
  TradeManager(const TradeManager &) = default;
  TradeManager &operator=(const TradeManager &) = default;
  ~TradeManager() = default;

  void add(const TradeInfo &trade) { _trades.emplace_back(trade); }

  void add(const std::vector<TradeInfo> trades) {
    for (auto &trade : trades) {
      _trades.emplace_back(trade);
    }
  }

  friend std::ostream &operator<<(std::ostream &os,
                                  const TradeManager &tradeLogger) {
    for (auto &trade : tradeLogger._trades) {
      os << "TRADE " << trade.instrument << " " << trade.sellOrderId << " "
         << trade.buyOrderId << " " << trade.quantity << " " << trade.price
         << "\n";
    }
    return os;
  }
};

#endif