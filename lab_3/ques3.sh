#ques3
#Write a shell script to replace all files with .txt extension with .text in the 
#current directory. This has to be done recursively i.e if the current folder contains a folder
#“OS” with abc.txt then it has to be changed to abc.text ( Hint: use find, mv )


#'find' command to get a list of all .txt files
echo "enter file name:"
FILES=$(find . -type f -name "*.txt")
for FILE in $FILES
do # 'sed' is a simple tool to swap text: s/old/new/
    NEW_NAME=$(echo $FILE | sed 's/\.txt/\.text/')
    mv "$FILE" "$NEW_NAME"
    echo "Changing $FILE to $NEW_NAME"
done

echo "Task completed!"