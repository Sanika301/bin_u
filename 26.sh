#!/bin/bash

# Function to download webpage at given URL
download_webpage() {
    local url="$1"

    echo "Downloading webpage from: $url"
    wget -q "$url" -O webpage.html

    if [ $? -eq 0 ]; then
        echo "Webpage downloaded successfully."
    else
        echo "Failed to download webpage."
    fi
}

# Main script

# Usage message
usage() {
    echo "Usage: $0 <url>"
    exit 1
}

# Check if URL argument is provided
if [ $# -ne 1 ]; then
    usage
fi

url="$1"

# Call function to download webpage
download_webpage "$url"
