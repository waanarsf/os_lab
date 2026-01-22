#ques4
#Write a shell script to calculate the gross salary. GS=Basics + TA + 10% of Basics.
#Floating point calculations has to be performed.
echo "Enter basic salary:"
read BASIC
echo "Enter Travel allowance:"
read TA
HRA=$(echo "scale=2; $BASIC * 0.1" | bc -l)
GROSS=$(echo "scale=2; $BASIC + $TA + $HRA" | bc -l)
echo " basic salary : $BASIC"
echo "TA: $TA"
echo "allowance: $HRA"
echo "gross salary: $GROSS"
