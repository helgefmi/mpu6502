CFLAGS=-O3 -Wall -Wextra -lboost_program_options-mt -lboost_filesystem-mt
SRC=src/Mpu6502.o src/main.o src/TestSuite.o
TARGET=mpu6502
CC=g++

all: $(SRC)
	$(CC) -o $(TARGET) $(SRC) $(CFLAGS)

clean:
	find -name \*.o -exec rm {} \;
	rm -f $(TARGET)
