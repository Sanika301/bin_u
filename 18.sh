#!/bin/bash

echo "Simple Calculator"
echo "-----------------"
echo "Enter first number:"
read num1
echo "Enter second number:"
read num2

echo "Select operation:"
echo "1. Addition (+)"
echo "2. Subtraction (-)"
echo "3. Multiplication (*)"
echo "4. Division (/)"
read choice

case $choice in
    1) result=$(echo "$num1 + $num2" | bc);;
    2) result=$(echo "$num1 - $num2" | bc);;
    3) result=$(echo "$num1 * $num2" | bc);;
    4) result=$(echo "scale=2; $num1 / $num2" | bc);;
    *) echo "Invalid choice"; exit 1;;
esac

echo "Result: $result"
