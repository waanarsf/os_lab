
#Write a shell script to find whether a given file is the directory or regular file.
PATH_TO_CHECK=$1

if [ -z "$PATH_TO_CHECK" ]; then
    echo "Please provide a file path."
    exit 1
fi

if [ -d "$PATH_TO_CHECK" ]; then
    echo "$PATH_TO_CHECK is a directory."
elif [ -f "$PATH_TO_CHECK" ]; then
    echo "$PATH_TO_CHECK is a regular file."
else
    echo "$PATH_TO_CHECK does not exist or is a special file (like a link or device)."
fi