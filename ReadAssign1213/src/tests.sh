#!/bin/bash

TEST_DIR=results
NUM_EVENTS=11
test_names=("L1_1"	"L1_2"	"L2_1"	"L2_2" "L3_1" 	"L3_2"	"RAM_1"	"RAM_2" )
test_sizes=(50		50		146		 146	 500  	 500	 800	 800	) 
test_flags=(0		1 		 0		   1       0       1      0       1     )


rm -rf $TEST_DIR
mkdir $TEST_DIR


index=0

while ((index < 8)); do

	rm -rf $TEST_DIR/${test_names[$index]}
	mkdir $TEST_DIR/${test_names[$index]}

	TIME_FILE=$TEST_DIR/${test_names[$index]}/times
	ORDERED_TIME_FILE=$TIME_FILE.ordered
	touch $TIME_FILE
	touch $ORDERED_TIME_FILE

	let run=0;

	#3 runs for each test
	while((run <= 3)); do		
		EVENTS_FILE=$TEST_DIR/${test_names[$index]}/events.$run
		touch $EVENTS_FILE
		
		#run tests
		echo "Running test named" ${test_names[$index]} "with matrix size n=" ${test_sizes[$index]} " and op=" ${test_flags[$index]}
		echo -n "	"
		let test_index=0
		while ((test_index < NUM_EVENTS)); do
			echo -n "$test_index "
			./papi_test ${test_sizes[$index]} ${test_flags[$index]} $test_index >> $EVENTS_FILE
			let test_index++
		done
		echo ""

		echo -n "$run " >> $TIME_FILE
		awk '{sum+=$3} END {print sum/NR}' $EVENTS_FILE >> $TIME_FILE
		sort -t' ' -k2 $TIME_FILE > $ORDERED_TIME_FILE
		
		let run++
	done

	# checks 5% error margin
	res=`awk 'BEGIN {res=1} {if (NR == 1) {x=$2} else if (($2 - x) / x > 0.5) {res=0}} END {print res}' $ORDERED_TIME_FILE`

	# if result is true, keep going, else repeat 
	if ((res==1)); then
	 	let index++
	else
		echo "margin error not met, restarting"
	fi

done