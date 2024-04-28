#!/bin/bash

# Array to hold the 10 numbers
numbers=(5 2 9 1 7 4 8 3 10 6)

# Sorting the numbers in ascending order
sorted_numbers=($(printf "%s\n" "${numbers[@]}" | sort -n))

# Print the sorted numbers
echo "Sorted numbers in ascending order:"
for num in "${sorted_numbers[@]}"; do
    echo $num
done
