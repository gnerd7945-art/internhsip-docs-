#!/bin/bash

# --- Configuration ---
IMAGE_DIR="./images"       # Folder with your .jpg files
CSV_FILE="./csv/data.csv"      # Your saved CSV file
OUTPUT_DIR="./organized"   # The folder where the results will go

# Create the output directory
mkdir -p "$OUTPUT_DIR"

# Loop through all JPG files
for img_path in "$IMAGE_DIR"/*.jpg; do
    
    # Skip if no jpgs exist
    [ -e "$img_path" ] || continue

	echo $img_path
    # Extract filename without .jpg (e.g., "03")
    filename=$(basename "$img_path" .jpg)

    # Convert to standard integer to match CSV (e.g., "03" -> "3")
    clean_id=$((10#$filename))

    # Search CSV, grab name, and fix the spaces/underscores
    emp_name=$(awk -F',' -v search_id="$clean_id" '
        NR > 1 { 
            csv_id = $1 + 0
            
            if (csv_id == search_id) {
                name = $2
                gsub(/\r/, "", name)      # Remove invisible Windows carriage returns
                gsub(/^ +| +$/, "", name) # Trim leading and trailing spaces
                gsub(/ +/, "_", name)     # Convert multiple spaces into a single underscore
                print name
                exit
            }
        }
    ' "$CSV_FILE")

    # If a match was found
    if [ -n "$emp_name" ]; then
        
        # Create a folder for this ID
        new_folder="$OUTPUT_DIR/$filename"
        mkdir -p "$new_folder"

        # Copy image and create the name.txt file
        cp "$img_path" "$new_folder/"
        echo "$emp_name" > "$new_folder/name.txt"

        echo "✅ Success: $filename.jpg -> Folder created with name.txt ($emp_name)"
    else
        echo "⚠️ Warning: No match found for $filename.jpg"
    fi

done

echo "Process complete! Check the '$OUTPUT_DIR' folder."
