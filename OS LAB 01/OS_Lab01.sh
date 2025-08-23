#!/bin/bash

# Name: Ajitesh Rastogi
# Assignment: OS Lab 1

# Function to organize files by extension
organize_files() {
    read -p "Enter directory path to organize: " dir

    # Check if directory exists
    if [ ! -d "$dir" ]; then
        echo "Directory does not exist. Please try again."
        return
    fi

    # Loop through each file in directory
    for file in "$dir"/*; do
        if [ -f "$file" ]; then
            # Extract the filename (without path)
            filename=$(basename -- "$file")

            # Extract extension: part after last '.' if any
            ext="${filename##*.}"

            # If no extension (filename same as ext), move to no_ext folder
            if [ "$ext" = "$filename" ]; then
                ext="no_ext"
            fi

            # Create extension folder if not present
            mkdir -p "$dir/$ext"
            # Move file to the extension folder
            mv "$file" "$dir/$ext/"
        fi
    done

    echo "Files organized by extension in $dir."
}

# Function to ping subnet and find live hosts
ping_subnet() {
    read -p "Enter subnet prefix (e.g. 192.168.1.): " subnet

    echo "Scanning subnet $subnet1 to .254..."

    # Loop 1 to 254 and ping in background
    for i in $(seq 1 254); do
        ip="${subnet}${i}"
        # Ping once, wait max 1 second for reply, suppress output
        ping -c 1 -W 1 "$ip" &> /dev/null && echo "$ip is alive" &
    done

    # Wait for all background pings to complete
    wait

    echo "Subnet scan complete."
}

# Main menu loop
while true; do
    echo ""
    echo "===== Shell Utility Toolkit Menu ====="
    echo "1. Organize files by extension"
    echo "2. Network scan (ping subnet)"
    echo "3. Exit"
    echo "======================================"
    read -p "Enter your choice: " choice

    case $choice in
        1)
            organize_files
            ;;
        2)
            ping_subnet
            ;;
        3)
            echo "Exiting script. Goodbye!"
            exit 0
            ;;
        *)
            echo "Invalid choice. Please enter 1, 2, or 3."
            ;;
    esac
done
