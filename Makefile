# makefile for scheduling program

CXXFLAGS = -g -std=c++17 -Wall -Wextra -Wpedantic -fsanitize=address

TARGETS = driver libschedule_rr.so libschedule_fcfs.so libschedule_sjf.so libschedule_priority.so libschedule_priority_rr.so
LDLIBS = -ldl

.PHONY: clean

all: $(TARGETS)

driver: driver.o schedulers.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDLIBS)

driver.o: driver.cpp task.h schedulers.h cpu.h
	$(CXX) $(CXXFLAGS) -c $<

schedulers.o: schedulers.cpp schedulers.h
	$(CXX) $(CXXFLAGS) -fPIC -c $<

cpu.o: cpu.cpp task.h
	$(CXX) $(CXXFLAGS) -fPIC -c $<

libschedule_rr.so: schedule_rr.cpp schedulers.o cpu.o
	$(CXX) $(CXXFLAGS) -fPIC -shared $^ -o $@

libschedule_fcfs.so: schedule_fcfs.cpp schedulers.o cpu.o
	$(CXX) $(CXXFLAGS) -fPIC -shared $^ -o $@

libschedule_sjf.so: schedule_sjf.cpp schedulers.o cpu.o
	$(CXX) $(CXXFLAGS) -fPIC -shared $^ -o $@

libschedule_priority.so: schedule_priority.cpp schedulers.o cpu.o
	$(CXX) $(CXXFLAGS) -fPIC -shared $^ -o $@

libschedule_priority_rr.so: schedule_priority_rr.cpp schedulers.o cpu.o
	$(CXX) $(CXXFLAGS) -fPIC -shared $^ -o $@

test: $(TARGETS)
	./driver ./libschedule_rr.so schedules/book.txt
	./driver ./libschedule_fcfs.so schedules/book.txt
	./driver ./libschedule_sjf.so schedules/book.txt
	./driver ./libschedule_priority.so schedules/book.txt
	./driver ./libschedule_priority_rr.so schedules/book.txt

clean:
	rm -rf *.o $(TARGETS)
