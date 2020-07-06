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
echo 1 >> test/out
fi

name=$(echo "$file" | cut -f 1 -d '.')
if ! [ -f ""$name".out" ]; then
echo "Out file for "$name" not found"
exit
fi
diff test/out ""$name".out"
if [ $? != 0 ] && [ err1 == 0 ]; then
res[i]=""$name" failed"
i=$i+1
fi
done


echo 
echo 
echo
for msg in "${res[@]}"; do
echo $msg
done
