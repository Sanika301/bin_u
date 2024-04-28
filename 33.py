#!/usr/bin/env python3

import os

# Function to check if a file is executable
def check_executable(filename):
    if os.access(filename, os.X_OK):
        print(f"{filename} is executable.")
        return True
    else:
        print(f"{filename} is not executable.")
        return False

# Function to remove execute permissions from a file
def remove_execute_permissions(filename):
    os.chmod(filename, 0o644)
    print(f"Execute permissions removed from {filename}.")

# Main script

# Usage message
def usage():
    print("Usage: ./33.py <filename>")
    exit(1)

# Check if filename argument is provided
import sys
if len(sys.argv) != 2:
    usage()

filename = sys.argv[1]

# Check if file exists
if not os.path.exists(filename):
    print(f"Error: File '{filename}' does not exist.")
    exit(1)

# Check if file is executable
if check_executable(filename):
    # If file is executable, remove execute permissions
    remove_execute_permissions(filename)
