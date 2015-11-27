#CC    = g++
CC   = clang++-3.6 -L /usr/lib/gcc/x86_64-linux-gnu/4.8 -I /usr/include/x86_64-linux-gnu/c++/4.8 -I /usr/include/c++/4.8 

FLAGS = -std=c++11 -O2 -Wall -pedantic

# 
yourprogram.out: # your dependencies here
	 $(CC) $(FLAGS) -o yourprogram.out calendar15test.cpp kattistime.cpp # your files here

youroutputs:
	cat calendar15.01.in | ./yourprogram.out > calendar15.01.out
	cat calendar15.02.in | ./yourprogram.out > calendar15.02.out
	cat calendar15.03.in | ./yourprogram.out > calendar15.03.out
	cat calendar15.04.in | ./yourprogram.out > calendar15.04.out
	cat calendar15.05.in | ./yourprogram.out > calendar15.05.out
	cat calendar15.06.in | ./yourprogram.out > calendar15.06.out
	cat calendar15.07.in | ./yourprogram.out > calendar15.07.out
	cat calendar15.08.in | ./yourprogram.out > calendar15.08.out
	cat calendar15.09.in | ./yourprogram.out > calendar15.09.out

answers:
	cat calendar15.01.in | ./calendar15test.out > calendar15.01.ans
	cat calendar15.02.in | ./calendar15test.out > calendar15.02.ans
	cat calendar15.03.in | ./calendar15test.out > calendar15.03.ans
	cat calendar15.04.in | ./calendar15test.out > calendar15.04.ans
	cat calendar15.05.in | ./calendar15test.out > calendar15.05.ans
	cat calendar15.06.in | ./calendar15test.out > calendar15.06.ans
	cat calendar15.07.in | ./calendar15test.out > calendar15.07.ans
	cat calendar15.08.in | ./calendar15test.out > calendar15.08.ans
	cat calendar15.09.in | ./calendar15test.out > calendar15.09.ans

