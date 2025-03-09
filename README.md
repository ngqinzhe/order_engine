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
#### Command to run Program
```
cat sample_input.txt | ./run.sh
```
#### Command to run Tests
```
./test.sh
```
If you face error during this, it is likely you need to clean up the previous build file from `run.sh`. You can `rm -rf build` and run `./test.sh` again.
