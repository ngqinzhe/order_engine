#include "orderengine.hpp"
#include "orderparser.hpp"
#include <gtest/gtest.h>
#include <iostream>
#include <string>

TEST(OrderEngineTest1, TestNoMatch) {
  auto engine = OrderEngine();
  auto parser = OrderParser();
  std::string buffer = "12345 BUY BTCUSD 5 10000";
  std::istringstream iss{buffer};

  auto orders = parser.parse(iss);
  for (auto &order : orders)
    engine.insertOrder(order);

  std::ostringstream result;
  result << engine;
  ASSERT_EQ(result.str(), "\n12345 BUY BTCUSD 5 10000\n");
}

TEST(OrderEngineTest2, TestExactMatch) {
  auto engine = OrderEngine();
  auto parser = OrderParser();

  std::string buffer = "abc BUY BTCUSD 5 1\ndef SELL BTCUSD 5 1";
  std::istringstream iss{buffer};

  auto orders = parser.parse(iss);
  for (auto &order : orders)
    engine.insertOrder(order);

  std::ostringstream result;
  result << engine;
  ASSERT_EQ(result.str(), "TRADE BTCUSD def abc 5 1\n\n");
}

TEST(OrderEngineTest3, TestMultipleInstrumentsNoMatch) {
  auto engine = OrderEngine();
  auto parser = OrderParser();

  std::string buffer = "abc BUY BTCUSD 5 1\ndef SELL ETHUSD 5 1";
  std::istringstream iss{buffer};

  auto orders = parser.parse(iss);
  for (auto &order : orders)
    engine.insertOrder(order);

  std::ostringstream result;
  result << engine;
  ASSERT_EQ(result.str(), "\nabc BUY BTCUSD 5 1\ndef SELL ETHUSD 5 1\n");
}

TEST(OrderEngineTest4, TestPriceTimePriorityResult) {
  auto engine = OrderEngine();
  auto parser = OrderParser();

  std::string buffer =
      "abc BUY BTCUSD 5 1\ndef BUY BTCUSD 5 2\nijk BUY BTCUSD 5 3";
  std::istringstream iss{buffer};

  auto orders = parser.parse(iss);
  for (auto &order : orders)
    engine.insertOrder(order);

  std::ostringstream result;
  result << engine;
  ASSERT_EQ(result.str(),
            "\nabc BUY BTCUSD 5 1\ndef BUY BTCUSD 5 2\nijk BUY BTCUSD 5 3\n");
}

TEST(OrderEngineTest5, TestMultiFill) {
  auto engine = OrderEngine();
  auto parser = OrderParser();

  std::string buffer =
      "abc BUY BTCUSD 5 1\ndef BUY BTCUSD 5 2\nijk SELL BTCUSD 10 1";
  std::istringstream iss{buffer};

  auto orders = parser.parse(iss);
  for (auto &order : orders)
    engine.insertOrder(order);

  std::ostringstream result;
  result << engine;
  ASSERT_EQ(result.str(),
            "TRADE BTCUSD ijk def 5 2\nTRADE BTCUSD ijk abc 5 1\n\n");
}