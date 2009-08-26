test plp null
    PHP
    PLP
    .byte $2
assert reg.pc 3
assert reg.ps 0

test plp c flag
    SEC
    PHP
    CLC
    PLP
    .byte $2
assert reg.pc 5
assert reg.ps 1

test plp d flag
    SED
    PHP
    SEI
    PLP
    .byte $2
assert reg.pc 5
assert reg.ps 0x8

test plp i flag
    SEI
    PHP
    CLI
    PLP
    .byte $2
assert reg.pc 5
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
    .byte $2
assert reg.pc 9
assert reg.ps 0xD
