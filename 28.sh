#!/bin/bash

# Function to display users using finger command
display_users_with_finger() {
    echo "Users on the system (using finger command):"
    finger
}

# Function to display users using who command
display_users_with_who() {
    echo "Users on the system (using who command):"
    who
}

# Main script

# Usage message
usage() {
    echo "Usage: $0 [-f | -w]"
    echo "Options:"
    echo "  -f : Use finger command"
    echo "  -w : Use who command (default)"
    exit 1
}

# Check for command-line options
while getopts "fw" opt; do
    case $opt in
        f)
            display_users_with_finger
            exit
            ;;
        w)
            display_users_with_who
            exit
            ;;
        *)
            usage
            ;;
    esac
done

# If no option is provided, default to using who command
display_users_with_who
