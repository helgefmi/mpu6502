test mul 7 * 8
    LDA #7
    LDX #8
    JSR mulx
    .byte 2

mulx:
    STA $50
    LDA #0
mulx_top:
    CLC
    ADC $50

    DEX
    BNE mulx_top

    RTS
assert reg.ac 56


test nfac 5
    LDA #5
    JSR nfac
    .byte 2

nfac:
    TAY
nfac_top:
    DEY
    BEQ nfac_bot
    STY $55
    LDX $55
    JSR mulx
    JMP nfac_top

nfac_bot:
    RTS

mulx:
    STA $50
    LDA #0
mulx_top:
    CLC
    ADC $50

    DEX
    BNE mulx_top

    RTS

assert reg.ac 120
