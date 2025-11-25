#!/bin/bash

no_tests=10000000

for((i=0;i<no_tests;i++))
do
	echo $i > input.in
	./gen < input.in > input.in
	./t1 < input.in > t1.out
	./t2 < input.in > t2.out 
	if diff -b t1.out t2.out
	then
		echo -ne "$i\r"
	else
		echo $i
		break
	fi
done
echo "OK"
