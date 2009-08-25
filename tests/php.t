test php null
    PHP
assert reg.p 1
assert mem.0x1FF 0x0

test php c flag
    SEC
    PHP
assert reg.p 2
assert mem.0x1FF 0x1

test php d flag
    SED
    PHP
assert reg.p 2
assert mem.0x1FF 0x8

test php i flag
    SEI
    PHP
assert reg.p 2
assert mem.0x1FF 0x4

test php cdi flag
    SEC
    SED
    SEI
    PHP
assert reg.p 4
assert mem.0x1FF 0xD
