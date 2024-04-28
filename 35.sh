#!/bin/bash

# Check if the number of arguments is less than 2
if [ "$#" -lt 2 ]; then
    echo "Error: Please provide 2 or more filenames."
    exit 1
fi

# Loop through each argument
for file in "$@"; do
    # Check if the file exists
    if [ ! -f "$file" ]; then
        echo "Error: File '$file' does not exist."
        exit 1
    fi
done

# Concatenate files
cat "$@" > concatenated_file.txt
echo "Files concatenated successfully. Output saved to concatenated_file.txt."
