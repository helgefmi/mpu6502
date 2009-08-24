CC=g++
CPPFLAGS=-O3 -Wall -Wextra -lboost_program_options-mt -lboost_filesystem-mt

SRC=src/Mpu6502.o src/main.o src/TestSuite.o
TARGET=mpu6502

all: $(SRC)
	$(CC) -o $(TARGET) $(SRC) $(CPPFLAGS)

clean:
	rm -f $(TARGET) src/*.o
