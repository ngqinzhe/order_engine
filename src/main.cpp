#include "../include/orderengine.hpp"
#include <iostream>
#include <sstream>
#include <stdio.h>
#include "../include/orderparser.hpp"

int main() {
  auto orderEngine = OrderEngine();
  auto orderParser = OrderParser();

  std::cerr << "====== Match Engine =====\n\n";
  auto orders = orderParser.parse(std::cin);
  for (auto &order : orders) {
    orderEngine.insertOrder(order);
  }
  std::cout << orderEngine;
  return 0;
}
