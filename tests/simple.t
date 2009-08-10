test lda_imm
    LDA #10
assert reg.a 10
assert reg.p 2

test lda_imm_sta_abs
    LDA #12
    STA $500
assert reg.p 5
assert mem.500 12

test lda_imm_sta_zero
    LDA #12
    STA $10
assert reg.p 4
assert mem.10 12
