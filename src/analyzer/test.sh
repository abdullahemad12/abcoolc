#!/bin/sh
# A simple shell script for testing

make semant
err=$?
if [ $err != 0 ]; then 
echo Failed to compile semant
fi


i=0
for file in test/*.cl; do
rm test/out
out1=$(./mysemant "$file") >test/out
err1=$?
if [ err1 != 0 ]; then
rm test/out
echo semerror >> test/out
fi


if [ -f ""$file".out" ]; then
echo "Out file for "$file" not found"
exit
fi
diff test/out ""$file".out"
if [ $? != 0 ] && [ err1 == 0 ]; then
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
