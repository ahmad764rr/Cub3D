#!/bin/bash

# Change "maps" to the directory you want to search
#!/bin/bash

# Ask if run with valgrind
read -p "Do you want to run with valgrind? (yes/no): " use_valgrind

# Ask for directory
read -p "Enter directory to search for .cub files (default: maps): " dir
dir=${dir:-maps}   # if empty, default = maps

# Check directory exists
if [ ! -d "$dir" ]; then
    echo "Error: Directory '$dir' not found."
    exit 1
fi

# Find and run tests
for file in $(find "$dir" -type f -name "*.cub"); do
    echo "Testing: $file"
    if [ "$use_valgrind" = "yes" ]; then
        valgrind ./cub3d "$file"
    else
        ./cub3d "$file"
    fi
    echo "---------------------------------"
done


# This script finds all .cub files in the "maps" directory and runs the cub3d program on each file, printing the name of the file being tested.
# Make sure to give execute permission to this script before running it:
# chmod +x run_tests.sh
# Then you can run it with:
# ./run_tests.sh