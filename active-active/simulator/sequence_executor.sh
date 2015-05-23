#!/bin/bash

placeholder="PLACEHOLDER";
debug="&2"
simulator="./simulator"
results_parser="../results_parser/results_parser"

if [[ ! -f ${simulator} ]]
then
	echo "${simulator} does not exists"
	exit 1
fi

if [[ ! -f ${results_parser} ]]
then
	echo "${results_parser} does not exists"
	exit 1
fi

if [ $# -ne "3" ]
then
  echo "Usage: ./sequence_executor.sh settings_ini_template value_set_file results_folder_name"  
  echo "settings_ini_template should contain ${placeholder} instead of desired parameter value"
  exit 1
fi

# {line} line from value_set file
# {N} number of parameter value starting from 0
# {return} Nth parameter value
function getNthValueFromValueSetLine {
	line=$1
	N=$2
        result=`echo ${line} | cut -d \  -f $((N+2))`
	#echo "getNthValueFromValueSetLine : ${line} | ${N} | ${result}" >&2
	echo ${result}
}

# {line} line from  value_set file
# {return} returns number of values in line
function getValueSetSize {
	line=$1
	N=`echo ${i_line} | wc -w`;
	N=$((N-1))
	#echo "getValueSetSize : ${line} ${N}" >&2
        echo ${N} 
}

# {param} file with value_set
# {param} file for points cache
# {return} number of points in file to model
function getNumberOfPointsAndGeneratePointsFile {
	file=$1;
	points_file=$2;
	n=`cat ${file} | wc -l`;
	m=1;
	for (( i=${n}; i>0; i-- ))
	do
		i_line=`sed "${i}q;d" ${file}`;
		N=`echo ${i_line} | wc -w`
		N=$((N-1));
		m=$((m*N));

	done
	echo 'Going to main loop' >&2
	for (( i=0; i<${m}; i++))
	do
		line_to_write="";
		N=${m};
		current_i=$i;
		for (( j=1; j<=${n}; j++ ))
		do
			
			i_line=`sed "${j}q;d" ${file}`;
	#		echo "doing getValueSetSize" >&2
			# Number of values for j param
			current_N=`getValueSetSize "${i_line}"`;
	#		echo "after getValueSetSize" >&2
			N=$((N/current_N));
			k=$((current_i/N));
			current_i=$((current_i - N*k));
         #               echo "before getNthValueFromValueSetLine" >&2
			new_number=`getNthValueFromValueSetLine "${i_line}" ${k}` #$((start_val+k*step));
			line_to_write="${line_to_write} ${new_number}";
	#		echo "j = ${j}, i_line = ${i_line}, new_number = ${new_number}" >&2
		done
		
		echo ${line_to_write} >> ${points_file}
	done

	echo ${m}
}

# {param} file
# {return} string with parameters names
function getResultsHeader {
	headers=`cat $1 | grep -o '^[^ ]*'`;
	echo $headers
} 

# {param} file name
# {param} number of the point
# {return} point string
function getCurrentPoint {
	sed "$2q;d" $1
}

# {param} file to substitute
# {param} settings file
# {param} point string
function substituteCurrentPoint {
	new_file=$1;
	source_file=$2;
	point=$3;
	cp ../${source_file} ${new_file}
	i=0;
	for value in ${point}
	do
		sed -i "s/${placeholder}${i}/${value}/g" ${new_file} 
		((i++));	
	done
	
} 

# {file} config ini file to parse
# {return} value of MODELING_STEPS_NUMBER param from $file
function getStepsNumber {
	file=$1
	result=`cat ${file} | grep  MODELING_STEPS_NUMBER= | grep -o '[^=]*$'`
	echo ${result}
}


settings_file=$1;
value_set_file=$2;
results_folder=$3;
local_settings_file="local_settings.ini";
local_points_file="local_points_file";

results_header=`getResultsHeader ${value_set_file}`;

results_file="results.file";
tmp_results="tmp.results";

mkdir ${results_folder}
cd ${results_folder}

number_of_points=`getNumberOfPointsAndGeneratePointsFile ../${value_set_file} ${local_points_file}`;

echo "number_of_points= ${number_of_points}" >&2
echo "Start modeling" >&2

echo "${results_header} performance IOPS latency" > ${results_file}

for (( c=1; c<=${number_of_points}; c++ ))
do
	# Main loop
	echo "Doing ${c}/${number_of_points} point" >&2
	current_point=`getCurrentPoint ${local_points_file} ${c}`;
	substituteCurrentPoint ${local_settings_file} ${settings_file} "${current_point}"
	#sed -e "s/${placeholder}/${c}/g" ../${settings_file} > ${local_settings_file}
	echo "Started at:"
	date -R
	../${simulator} ${local_settings_file} 2>/dev/null 
	# Calculating performance
	steps_number=`getStepsNumber *.ini`
	echo "steps_number=${steps_number}" >&2
	echo "../${results_parser} aa* ${steps_number} 1 1 2>&1"
	performance=`../${results_parser} aa* ${steps_number} 1 1 2>&1`
	echo "Finished at:"
        date -R
	result_line=`echo "${current_point} ${performance}" | sed -e "s/\./,/g"`
	echo "${result_line}" >> ${results_file}		
	echo "${result_line}"
	cp aa* results_$c
#	cp *.ini settings_$c
	rm aa* *.ini
done

rm ${local_points_file}
