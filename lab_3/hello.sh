#!/bin/bash
echo "enter two numbers"
read a b
echo a is $a and b is $b
c=$((a/b))
echo $c
c=`expr $a \* $b`
echo $c 
c=$(echo $a/$b | bc -l)
echo $c
c=`bc -l <<< $a/$b`
echo $c
c=$(bc -l <<< $a/$b)
echo $c
### control flow
if(($a>$b))
then
	echo $a is greater than $b
else
	echo $b is greater than $a
fi
