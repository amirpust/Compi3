#!/bin/bash

echo "
   __                          _                  _             _  _             
  / _|                        | |                | |           | || |            
 | |_   _ __    ___    ___    | |_    ___   ___  | |_   ___    | || |_     _   _ 
 |  _| | '__|  / _ \  / _ \   | __|  / _ \ / __| | __| / __|   |__   _|   | | | |
 | |   | |    |  __/ |  __/   | |_  |  __/ \__ \ | |_  \__ \      | |     | |_| |
 |_|   |_|     \___|  \___|    \__|  \___| |___/  \__| |___/      |_|      \__,_|
                                                                                  
"


echo "Running test 1"
./hw3 < oy_tests/oy1.in 2>&1 > oy_tests/oy1.res
diff oy_tests/oy1.res oy_tests/oy1.out
echo "Running test 2"
./hw3 < oy_tests/oy2.in 2>&1 > oy_tests/oy2.res
diff oy_tests/oy2.res oy_tests/oy2.out
echo "Running test 3"
./hw3 < oy_tests/oy3.in 2>&1 > oy_tests/oy3.res
diff oy_tests/oy3.res oy_tests/oy3.out