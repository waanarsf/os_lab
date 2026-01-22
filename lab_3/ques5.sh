#ques5
#Write a program to copy all the files (having file extension input by the user) in the
#current folder to the new folder input by the user. ex: user enter .text TEXT then all
#files with .text should be moved to TEXT folder. This should be done only at single
#level. i.e if the current folder contains a folder name ABC which has .txt files then
#these files should not be copied to TEXT.
#Write a shell script to modify all occurrences of “ex:” with “Example:” in all the files present

read -p "Enter file extension (e.g. .txt): " EXT
read -p "Enter destination folder name: " FOLDER
mkdir -p "$FOLDER"
cp *"$EXT" "$FOLDER/" 2>/dev/null
echo "All $EXT files have been copied to $FOLDER."
for FILE in *; do
    if [ -f "$FILE" ]; then
        sed -i 's/^ex:/Example:/g' "$FILE"
        sed -i 's/\.Example:/.Example:/g' "$FILE"
    fi
done

echo "Replacement complete."