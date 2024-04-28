#!/bin/bash

# Function to download a file from FTP server
download_file() {
    local ftp_server="$1"
    local file="$2"

    # Use lftp to connect to the FTP server and download the file
    lftp -e "get $file; quit" "$ftp_server"
}

# Main script

# Usage message
usage() {
    echo "Usage: $0 <ftp_server> <file>"
    exit 1
}

# Check if two arguments are provided
if [ $# -ne 2 ]; then
    usage
fi

ftp_server="$1"
file="$2"

# Check if lftp is installed
if ! command -v lftp &>/dev/null; then
    echo "Error: lftp command is not installed. Please install lftp."
    exit 1
fi

# Download the file from the FTP server
download_file "$ftp_server" "$file"
