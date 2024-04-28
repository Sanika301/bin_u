#!/bin/bash

# Define the FIFO name
FIFO_NAME="myfifo"

# Create the FIFO (named pipe)
if [ ! -p "$FIFO_NAME" ]; then
    mkfifo "$FIFO_NAME"
fi

# Function to read data from the FIFO
read_from_fifo() {
    echo "Reader process is listening for messages..."
    while read line < "$FIFO_NAME"; do
        echo "Received message: $line"
    done
}

# Function to write data to the FIFO
write_to_fifo() {
    echo "Enter message to send (or 'exit' to quit):"
    while true; do
        read message
        if [ "$message" = "exit" ]; then
            break
        fi
        echo "$message" > "$FIFO_NAME"
    done
}

# Check if the script is run with an argument
if [ $# -ne 1 ]; then
    echo "Usage: $0 [read|write]"
    exit 1
fi

# Check the argument and run the appropriate function
case "$1" in
    read) read_from_fifo ;;
    write) write_to_fifo ;;
    *) echo "Invalid argument: $1"; exit 1 ;;
esac


Run program in 2 terminals:
./fifo_shell.sh write

Terminal 2
./fifo_shell.sh read