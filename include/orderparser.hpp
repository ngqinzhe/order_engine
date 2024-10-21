#ifndef ORDERPARSER_HPP
#define ORDERPARSER_HPP
#pragma once
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <vector>
#include "order.hpp"

class OrderParser {
private:

public:
    OrderParser() {}
    OrderParser(const OrderParser&) = default;
    OrderParser& operator=(const OrderParser&) = default;
    ~OrderParser() = default;

    std::vector<Order> parse(std::istream& inputStream) {
        std::vector<Order> orders;
        std::string line;
        while (getline(inputStream, line)) {
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

            orders.emplace_back(order);
        }
        return orders;
    }
};

#endif