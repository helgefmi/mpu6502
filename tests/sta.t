test sta_abs
    LDA #12
    STA $1000
assert reg.p 5
assert mem.0x1000 12

test sta_zero
    LDA #12
    STA $10
assert reg.p 4
assert mem.0x10 12
