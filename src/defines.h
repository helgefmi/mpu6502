/* MEMORY AREA */
#define IO_START  0xD000
#define IO_END    0xDFFF

#define EEPROM_START 0xE000
#define EEPROM_END   0xFFFF

/* RAM AREA */
#define STACK_START 0x0100
#define STACK_END   0x01FF

/* FLAGS */
#define FLAG_NEGATIVE   (1<<7)
#define FLAG_OVERFLOW   (1<<6)
#define FLAG_BREAK      (1<<4)
#define FLAG_DECIMAL    (1<<3)
#define FLAG_INTERRUPT  (1<<2)
#define FLAG_ZERO       (1<<1)
#define FLAG_CARRY      (1<<0)
