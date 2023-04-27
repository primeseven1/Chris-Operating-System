# Python scripts won't show compiler warnings
echo "Do not use this if you want to see compiler warnings, this will start in 2 seconds"
sleep 2

# Checking the return value and if it fails, it does the python script will display the error message
python3 build_everything.py
if [ $? -eq 0 ]; then
    echo "Build completed successfully."
else
    echo "There was an error when building."
    exit 1
fi

python3 combine_binaries.py
if [ $? -eq 0 ]; then
    echo "Successfully combined the binaries."
else
    echo "Failed to combine the binaries."
    exit 1
fi