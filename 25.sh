#!/bin/bash

# Function to find a file using find command
find_file() {
    local file="$1"

    echo "Using find command:"
    find / -type f -name "$file" 2>/dev/null
}

# Function to find a file using locate command
locate_file() {
    local file="$1"

    echo "Using locate command:"
    locate "$file" 2>/dev/null
}

# Main script

# Usage message
usage() {
    echo "Usage: $0 <file_name>"
    exit 1
}

# Check if at least one argument is provided
if [ $# -ne 1 ]; then
    usage
fi

file_name="$1"

# Check if the find command is available
if command -v find &>/dev/null; then
    find_file "$file_name"
else
    echo "Error: 'find' command is not available."
fi

# Check if the locate command is available
if command -v locate &>/dev/null; then
    locate_file "$file_name"
else
    echo "Error: 'locate' command is not available."
fi
