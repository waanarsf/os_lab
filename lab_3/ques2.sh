# ques2
#Write a shell script to list all files (only file names) containing the input #pattern
#(string) in the folder entered by the user.
#!/bin/bash

echo "Enter the directory path:"
read DIR
echo "Enter the pattern to search for:"
read PATTERN

#Moveing  into that directory
cd "$DIR"

#Listing the files and filter by the pattern
echo "Files matching '$PATTERN' in $DIR:"
ls -p | grep -v / | grep "$PATTERN"