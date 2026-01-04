#!/bin/bash

# Set compiler options
opts="-DENABLE_ASSERT=1"

clang++ $opts main.cpp arena.cpp -o ./build/main

./build/main