CC = g++
LIBS = -lpthread
OBJ = main.o AddressGenerator.o BubbleSort.o CPU.o Clock.o HDD.o MMU.o Measurements.o NRU.o OS.o PageTable.o Process.o Processes.o RAM.o RandomWalk.o ReplaceAlgorithm.o TableEntry.o 
TARGET = MemSim
FLAGS = -g -std=c++11 -Wall -MMD -fmessage-length=0

all: $(TARGET)
clean:
	rm -fv $(OBJ) $(TARGET) *~ *.d

%.o : %.cpp
	$(CC) -c $(FLAGS) -o $@ $<

$(TARGET): $(OBJ)
	$(CC) -o $(TARGET) $(OBJ) $(LIBS)
