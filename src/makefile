install: test

test: main.o joystick_mapper.o lookuptable.o pid.o reference_change.o control_allocation.o
	g++ -o $@ $? -lm

main.o: main.cpp
	g++ -c $?

joystick_mapper.o: joystick_mapper.cpp
	g++ -c $?

lookuptable.o: lookuptable.cpp
	g++ -c $?

pid.o: pid.cpp 
	g++ -c $?

reference_change.o: reference_change.cpp
	g++ -c $?

control_allocation.o: control_allocation.cpp
	g++ -c $?

clean: 
	rm -rf *.o