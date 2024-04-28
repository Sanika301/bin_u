#!/bin/bash

# Function to check if file exists in a folder
check_file_in_folder() {
    local folder="$1"
    local file="$2"

    if [ -e "$folder/$file" ]; then
        echo "File '$file' exists in the folder '$folder'."
    else
        echo "File '$file' does not exist in the folder '$folder'."
    fi
}

# Function to check if file exists on the entire drive
check_file_on_drive() {
    local file="$1"

    if [ $(find / -name "$file" 2>/dev/null) ]; then
        echo "File '$file' exists on the drive."
    else
        echo "File '$file' does not exist on the drive."
    fi
}

# Main script

# Usage message
usage() {
    echo "Usage: $0 <file_name> [folder_path]"
    echo "If folder_path is not provided, the script will search on the entire drive."
    exit 1
}

# Check if at least one argument is provided
if [ $# -lt 1 ]; then
    usage
fi

file_name="$1"
folder_path="${2:-/}"  # Default to root directory if folder_path is not provided

if [ ! -e "$folder_path" ]; then
    echo "Error: Folder '$folder_path' does not exist."
    exit 1
fi

if [ -d "$folder_path" ]; then
    check_file_in_folder "$folder_path" "$file_name"
else
    echo "Error: '$folder_path' is not a directory."
    exit 1
fi

check_file_on_drive "$file_name"
