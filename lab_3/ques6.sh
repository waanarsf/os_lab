#ques6
#Write a shell script which deletes all the even numbered lines in a text file.
read -p "Enter the filename: " FILE
awk 'NR % 2 != 0' "$FILE" > temp.txt && mv temp.txt "$FILE"
echo "Even lines removed."