test lda_imm_nzflag
    LDA #$AB
    .byte $2
assert reg.p 3
assert flags.n 1
assert flags.z 0

test lda_imm_nzflag
    LDA #$AB
    LDA #0
    .byte $2
assert reg.p 5
assert flags.n 0
assert flags.z 1

test lda_imm_nzflag
    LDA #$a
    .byte $2
assert reg.p 3
assert flags.n 0
assert flags.z 0

test ldx_imm_nzflag
    LDX #$AB
    .byte $2
assert reg.p 3
assert flags.n 1
assert flags.z 0

test ldx_imm_nzflag
    LDX #$AB
    LDX #0
    .byte $2
assert reg.p 5
assert flags.n 0
assert flags.z 1

test ldx_imm_nzflag
    LDX #$A
    .byte $2
assert reg.p 3
assert flags.n 0
assert flags.z 0

test ldy_imm_nzflag
    LDY #$AB
    .byte $2
assert reg.p 3
assert flags.n 1
assert flags.z 0

test ldy_imm_nzflag
    LDY #$AB
    LDY #0
    .byte $2
assert reg.p 5
assert flags.n 0
assert flags.z 1

test ldy_imm_nzflag
    LDY #$A
    .byte $2
assert reg.p 3
assert flags.n 0
assert flags.z 0

test and_imm_nzflag
    LDA #$F0
    AND #$0F
    .byte $2
assert reg.p 5
assert flags.n 0
assert flags.z 1

test and_imm_nzflag
    LDA #$FF
    AND #$F0
    .byte $2
assert reg.p 5
assert flags.n 1
assert flags.z 0

test ora_imm_nzflag
    ORA #$00
    .byte $2
assert reg.p 3
assert flags.n 0
assert flags.z 1

test ora_imm_nzflag
    ORA #$80
    .byte $2
assert reg.p 3
assert flags.n 1
assert flags.z 0

test eor_imm_nzflag
    LDA #$70
    EOR #$70
    .byte $2
assert reg.p 5
assert flags.n 0
assert flags.z 1

test eor_imm_nzflag
    LDA #$85
    EOR #$05
    .byte $2
assert reg.p 5
assert flags.n 1
assert flags.z 0

test sbc_imm_nzflag
    LDA #$80
    SEC
    SBC #$80
    .byte $2
assert reg.p 6
assert flags.n 0
assert flags.z 1

test sbc_imm_nzflag
    LDA #$80
    SEC
    SBC #$81
    .byte $2
assert reg.p 6
assert flags.n 1
assert flags.z 0

test adc_imm_nzflag
    LDA #$80
    ADC #$80
    .byte $2
assert reg.p 5
assert flags.n 0
assert flags.z 1

test adc_imm_nzflag
    LDA #$80
    ADC #$7F
    .byte $2
assert reg.p 5
assert flags.n 1
assert flags.z 0
