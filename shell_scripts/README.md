[image_name.sh](#image_namesh)

#!/bin/bash

# 1. Configuring file paths to placeholder names
IMAGE_DIR="./images"
OUTPUT_DIR="./output"
SEARCH_ID="04" # Example search_id to match against CSV

# 2. Creating an output directory
# -p flag: create if doesn't exist, don't throw error if it does
mkdir -p "$OUTPUT_DIR"

# 3. Looping through each image in path
# * is a wildcard that changes according to different file names
for i in "$IMAGE_DIR"/*.jpg; do
    
    # Check if  found any files (prevents errors if directory is empty)
    [ -e "$i" ] || continue

    # 4. Extracting filename and removing extensions/preceding path
    # basename syntax: basename "path" "extension_to_remove"
    # Example: "usr/a/04.jpg" becomes "04"
    filename=$(basename "$i" .jpg)

    # 5. Use awk to perform programming logic and compare IDs
    # We compare the ID in the CSV to our search_id
    # If true, we store the result in emp_name
    emp_name=$(awk -v search_id="$SEARCH_ID" -F, '$1 == search_id {print $2}' data.csv)

    # 6. Create a new variable for the subfolder path
    new_folder="$OUTPUT_DIR/$filename"
    
    # Create the folder itself
    mkdir -p "$new_folder"

    # 7. Copy image and employee name to the new folder
    cp "$i" "$new_folder"
    echo "$emp_name" > "$new_folder/name.txt"

done
