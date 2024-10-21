#include "../include/orderengine.hpp"
#include "../include/orderparser.hpp"
#include <iostream>
#include <sstream>
#include <stdio.h>

int main() {
  auto orderEngine = OrderEngine();
  auto orderParser = OrderParser();

  std::cout << "====== Match Engine =====\n\n";
  auto orders = orderParser.parse(std::cin);
  for (auto &order : orders) {
    orderEngine.insertOrder(order);
  }
  std::cout << orderEngine;
  return 0;
}
