# Order Engine Submission
### Name: Ng Qin Zhe

## Instructions on how to run
Order inputs are created in the following format
```
e.g
(orderId)  (side)  (instrument)  (quantity) (price)
12345      BUY     BTCUSD        5          10000
```
Send different order inputs that are newline (`\n`) separated into a text file for example, to run the program
##### Example Input
```
12345 BUY BTCUSD 5 10000
zod42 SELL BTCUSD 2 10001
13471 BUY BTCUSD 6 9971
11431 BUY ETHUSD 9 175
abe14 SELL BTCUSD 7 9800
plu401 SELL ETHUSD 5 170
45691 BUY ETHUSD 3 180
```
#### Command
```
cat sample_input.txt | ./run.sh
```

## Problem Approach
### Design
For the design of the order engine system, it must accept orders of different price, quantity, side and instruments. It must be performant, and attain a low time complexity for most of its operations.

`insertOrder` & `matchOrder` is done consecutively, thus we need to ensure that the `bestPrice` from the `SELL` & `BUY` sides can be retrieved in `O(1)` time. 

To do this, we use `std::map<double, std::list<Order>`, which is essentially a self-balancing tree data structure to store `Orders` in price priority, insertion would be `O(log n)` and best order retrieval would be `O(1)`.

we use a `std::list` as the data structure to store `Orders`. We can store the `std::list<Order>::iterator` in a map to get quick access. This allows us to remove orders from the list in `O(1)` time.

#### Order Engine
At the top layer is the `OrderEngine` class, it is responsible for allocating instruments to their respective `Orderbook`.

#### Order Book
The second layer is a `Orderbook` class. `Orderbook` is responsible for handling incoming `Order`s by storing them into the `Orderbook` and matching them with the `BUY` price >= `SELL` price. 

#### Trade Manager
`TradeManager` is responsible for bookkeeping of all the trades that happen. It provides the function to print the all the trades that happened in every `Orderbook` in order.

#### Limit
The underlying data structure to store the orders is in a `Limit` class. `Limit` would hold the orders of a single side in a `map<double, list<OrderPointers>>`. This is because we want the orders to be sorted by price, depending on the side of orders to ensure that to get the `bestPrice()` we can do it in `O(1)`. It will also hold the the same order in a timestamp prioritized `list` to ensure that we know the order of the `Order`s by timestamp.

#### Order
`Order` class will store the respective information regarding a single order such as `orderId`, `instrument`, `price`, `quantity`, `side`, `timestamp`.

### Time Spent
4 hours.