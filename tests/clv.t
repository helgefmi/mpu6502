test clv_v_set_by_bit
    LDA #$FF
    STA $CD
    BIT $CD
    CLV
assert reg.p 7
assert flags.v 0
