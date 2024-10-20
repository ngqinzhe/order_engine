#include "orderengine.hpp"
#include <iostream>
#include <sstream>
#include <stdio.h>

int main() {
  auto orderEngine = OrderEngine();

  std::cerr << "====== Match Engine =====\n\n";
  std::string line;
  while (getline(std::cin, line)) {
    std::stringstream ss(line);
    std::string item;
    std::vector<std::string> orderInput;
    while (getline(ss, item, ' ')) {
      orderInput.emplace_back(item);
    }
    if (orderInput.size() != 5) {
      std::cerr << "invalid input\n";
      continue;
    }
    std::string orderId = orderInput[0], side = orderInput[1],
                instrument = orderInput[2];
    double quantity = std::stod(orderInput[3]),
           price = std::stod(orderInput[4]);
    auto order = Order(orderId, side, instrument, quantity, price);

    orderEngine.insertOrder(order);
  }
  std::cout << orderEngine;
  return 0;
}
