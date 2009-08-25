test plp null
    PHP
    PLP
assert reg.pc 2
assert reg.ps 0

test plp c flag
    SEC
    PHP
    CLC
    PLP
assert reg.pc 4
assert reg.ps 1

test plp d flag
    SED
    PHP
    SEI
    PLP
assert reg.pc 4
assert reg.ps 0x8

test plp i flag
    SEI
    PHP
    CLI
    PLP
assert reg.pc 4
assert reg.ps 0x4

test plp cdi flag
    SEC
    SED
    SEI
    PHP
    CLC
    CLD
    CLI
    PLP
assert reg.pc 8
assert reg.ps 0xD
