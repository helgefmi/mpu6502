CC=g++
CPPFLAGS=-O2 -g3 -Wall -Wextra -lboost_program_options -lboost_filesystem

SRC=src/Mpu6502.o src/main.o src/TestSuite.o src/Util.o
TARGET=mpu6502

all: $(SRC)
	$(CC) -o $(TARGET) $(SRC) $(CPPFLAGS)

clean:
	rm -f $(TARGET) src/*.o
