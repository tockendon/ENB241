all : verify testdate testdriver

# Class objects
obj/date.o : include/date.h src/date.cpp
	g++ -ansi -c -o obj/date.o -I include/ src/date.cpp

obj/time.o : include/time1.h src/time.cpp
	g++ -ansi -c -o obj/time.o -I include/ src/time.cpp

obj/datetime.o : include/date.h include/time1.h include/datetime.h src/datetime.cpp
	g++ -ansi -c -o obj/datetime.o -I include/ src/datetime.cpp


# Test objects
obj/verification.o : obj/date.o obj/time.o obj/datetime.o
	g++ -ansi -c -o obj/verification.o -I include/ src/verification.cpp

obj/testdate.o : include/date.h src/testdate.cpp
	g++ -ansi -c -o obj/testdate.o -I include/ src/testdate.cpp

obj/testdriver.o : include/date.h include/time1.h include/datetime.h src/testdriver.cpp
	g++ -ansi -c -o obj/testdriver.o -I include/ src/testdriver.cpp


# Test executables
testdate : obj/date.o obj/testdate.o
	g++ -o testdate obj/date.o obj/testdate.o

testdriver : obj/date.o obj/time.o obj/datetime.o obj/testdriver.o
	g++ -o testdriver obj/date.o obj/time.o obj/datetime.o obj/testdriver.o

testbad: obj/date.o obj/testdriver.o badlib.o
	g++ -o testbad obj/date.o obj/testdriver.o badlib.o


# Run tests
rundate : testdate
	./testdate

runtest : testdriver
	./testdriver

runbad : testbad
	./testbad


# Link verification
verify: obj/time.o obj/datetime.o obj/verification.o
	g++ -ansi -o verification obj/date.o obj/time.o obj/datetime.o obj/verification.o
	./verification


# type in "make clean" to remove all output files
clean :
	rm -f obj/*.o
	rm -f verification testdate testdriver testbad
