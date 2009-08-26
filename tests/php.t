test php null
    PHP
    .byte $2
assert reg.p 2
assert mem.0x1FF 0x0

test php c flag
    SEC
    PHP
    .byte $2
assert reg.p 3
assert mem.0x1FF 0x1

test php d flag
    SED
    PHP
    .byte $2
assert reg.p 3
assert mem.0x1FF 0x8

test php i flag
    SEI
    PHP
    .byte $2
assert reg.p 3
assert mem.0x1FF 0x4

test php cdi flag
    SEC
    SED
    SEI
    PHP
    .byte $2
assert reg.p 5
assert mem.0x1FF 0xD
