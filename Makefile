CFLAGS=-O3 -Wall -Wextra
SRC=src/Mpu6502.o src/main.o
TARGET=mpu6502
CC=g++

all: $(SRC)
	g++ -o $(TARGET) $(SRC)

clean:
	find -name \*.o -exec rm {} \;
	rm -f $(TARGET)
