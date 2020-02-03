#!/bin/bash
target:
	mpic++ prog1.cpp -o prog1 -I/usr/include/python2.7 -lpython2.7 -I/usr/local/lib/matplotlib-cpp-master
	g++ graphdartboard.cpp -o graph -I/usr/include/python2.7 -lpython2.7 -I/usr/local/lib/matplotlib-cpp-master
graph-processors:
	i=1; while [ "$$i" -le 16 ]; do \
		echo "Using $$i processors"; \
		mpirun -np "$$i" prog1 6000000 10; \
		i=$$((i + 1));\
	done
graph-darts:
	i=5000000; while [ "$$i" -le 10000000 ]; do \
		echo "Throwing $$i darts"; \
		mpirun -np 4 prog1 "$$i" 10; \
		i=$$((i + 1000000));\
	done
