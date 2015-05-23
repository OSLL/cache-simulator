#!/bin/bash

results_table="results_table"

for i in {1..10}
do

	results=`../../results_parser/results_parser $i.res 200 1 1 2>&1 | tail -n 1 | sed -e 's/\./,/g'`
	echo $results >> $results_table

done 
