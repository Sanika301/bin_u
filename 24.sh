#!/bin/bash

# Function to display disk partitions and their sizes
show_disk_partitions() {
    echo "Disk partitions and their sizes:"
    df -h
    echo ""
}

# Function to display disk usage (free space)
show_disk_usage() {
    echo "Disk usage (free space):"
    du -h /
}

# Main script
show_disk_partitions
show_disk_usage
