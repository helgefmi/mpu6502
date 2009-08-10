To compile mpu6502, you need the libboost-program_options and libboost-filesystem libraries and development files.
You might also need to edit the Makefile manually, and remove the '-mt' suffixes in CFLAGS.

To run the tests, you need xa (6502/R65C02/65816 cross-assembler) somewhere in $PATH.
