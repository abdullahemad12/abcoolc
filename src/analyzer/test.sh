#!/bin/sh


make semant
err=$?
if [ $err != 0 ]; then 
echo Failed to compile semant
fi


i=0
for file in test/*; do
out1=$(./mysemant "$file")
err1=$?
out2=$(../../bin/lexer "$file" | ../../bin/parser | ../../bin/semant)
err2=$?

if [ "$err1" != "$err2" ]; then
res[i]=""$file" failed"
i=$i+1
fi
if [ "$err1" == "$err2" ] && [ "$out1" != "$out2" ] && [ $err1 == 0 ]; then
res[i]=""$file" failed"
i=$i+1
fi
done


echo 
echo 
echo
for msg in "${res[@]}"; do
echo $msg
done