#!/bin/bash

TEST_DIR=results
test_names=("L1_1"	"L1_2"	"L2_1"	"L2_2" "L3_1" 	"L3_2"	"RAM_1"	"RAM_2")
test_sizes=(50		50		146		 146	 500  	 500	 800	 800	) 


rm -rf $TEST_DIR
mkdir $TEST_DIR