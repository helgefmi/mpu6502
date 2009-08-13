CFLAGS=-O3 -Wall -Wextra -lboost_program_options-mt -lboost_filesystem-mt
SRC=src/Mpu6502.o src/Memory.o src/main.o src/TestSuite.o
TARGET=mpu6502
CC=g++

all: $(SRC)
	$(CC) -o $(TARGET) $(SRC) $(CFLAGS)

src/Memory.o:
	$(CC) $(CFLAGS) -c src/Memory.cpp -o src/Memory.o

src/Mpu6502.o:
	$(CC) $(CFLAGS) -c src/Mpu6502.cpp -o src/Mpu6502.o

src/main.o: src/Mpu6502.o src/TestSuite.o
	$(CC) $(CFLAGS) -c src/main.cpp -o src/main.o

src/TestSuite.o: src/Mpu6502.o
	$(CC) $(CFLAGS) -c src/TestSuite.cpp -o src/TestSuite.o

clean:
	find -name \*.o -exec rm {} \;
	rm -f $(TARGET)
