# Class objects
obj/bank.o : include/bank.h src/bank.cpp
	g++ -c -o obj/bank.o -I include/ src/bank.cpp

obj/component.o : include/component.h src/component.cpp
	g++ -c -o obj/component.o -I include/ src/component.cpp

obj/powersystem.o : include/powersystem.h src/powersystem.cpp
	g++ -c -o obj/powersystem.o -I include/ src/powersystem.cpp

obj/inverter.o : include/inverter.h src/inverter.cpp
	g++ -c -o obj/inverter.o -I include/ src/inverter.cpp

obj/location.o : include/location.h src/location.cpp
	g++ -c -o obj/location.o -I include/ src/location.cpp

obj/wire.o : include/wire.h src/wire.cpp
	g++ -c -o obj/wire.o -I include/ src/wire.cpp

obj/costbenefit.o : include/costbenefit.h src/costbenefit.cpp
	g++ -c -o obj/costbenefit.o -I include/ src/costbenefit.cpp

# Test objects
obj/testcomponent.o : src/testcomponent.cpp
	g++ -c -o obj/testcomponent.o -I include/ src/testcomponent.cpp

obj/testlocation.o : src/testlocation.cpp
	g++ -c -o obj/testlocation.o -I include/ src/testlocation.cpp

obj/testcostbenefit.o : src/testcostbenefit.cpp
	g++ -c -o obj/testcostbenefit.o -I include/ src/testcostbenefit.cpp

# Main object
obj/main.o : src/main.cpp
	g++ -c -o obj/main.o -I include/ src/main.cpp

# Test executables
testcomponent : obj/bank.o obj/component.o obj/inverter.o obj/wire.o obj/testcomponent.o
	g++ -o testcomponent obj/bank.o obj/component.o obj/inverter.o obj/wire.o obj/testcomponent.o

testlocation : obj/location.o obj/testlocation.o
	g++ -o testlocation obj/location.o obj/testlocation.o

testcostbenefit : obj/costbenefit.o obj/location.o obj/testcostbenefit.o
	g++ -o testcostbenefit obj/costbenefit.o obj/location.o obj/testcostbenefit.o

all: obj/bank.o obj/component.o obj/powersystem.o obj/inverter.o obj/location.o obj/wire.o obj/costbenefit.o obj/main.o obj/testcomponent.o obj/testlocation.o obj/testcostbenefit.o
	g++ -o main obj/bank.o obj/component.o obj/powersystem.o obj/inverter.o obj/location.o obj/wire.o obj/costbenefit.o obj/main.o
	g++ -o testcomponent obj/bank.o obj/component.o obj/inverter.o obj/wire.o obj/testcomponent.o
	g++ -o testlocation obj/location.o obj/testlocation.o
	g++ -o testcostbenefit obj/costbenefit.o obj/location.o obj/testcostbenefit.o

# Run tests
runtestcomponent : testcomponent
	./testcomponent

runtestlocation : testlocation
	./testlocation

runtestcostbenefit : testcostbenefit
	./testcostbenefit

# type in "make clean" to remove all output files
clean :
	rm -f obj/*.o
	rm -f testcomponent
	rm -f main
	rm -f testlocation
	rm -f testcostbenefit
