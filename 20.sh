#!/bin/bash

# Define the IP address to ping
ip_address="192.168.255.255"  
# This IP is typically outside of the local network range

# ip_address="8.8.8.8"  
# Google's public DNS server

# Ping the IP address once with a timeout of 2 seconds
ping -c 1 -W 2 $ip_address > /dev/null 2>&1

# Check the exit status of the ping command
if [ $? -eq 0 ]; then
    echo "The system is connected to the network."
else
    echo "The system is not connected to the network."
fi
