test lda_imm_nzflag
    LDA #$AB
assert flags.n 1
assert flags.z 0

test lda_imm_nzflag
    LDA #$AB
    LDA #0
assert flags.n 0
assert flags.z 1

test lda_imm_nzflag
    LDA #$a
assert flags.n 0
assert flags.z 0

test ldx_imm_nzflag
    LDX #$AB
assert flags.n 1
assert flags.z 0

test ldx_imm_nzflag
    LDX #$AB
    LDX #0
assert flags.n 0
assert flags.z 1

test ldx_imm_nzflag
    LDX #$A
assert flags.n 0
assert flags.z 0

test ldy_imm_nzflag
    LDY #$AB
assert flags.n 1
assert flags.z 0

test ldy_imm_nzflag
    LDY #$AB
    LDY #0
assert flags.n 0
assert flags.z 1

test ldy_imm_nzflag
    LDY #$A
assert flags.n 0
assert flags.z 0

test and_imm_nzflag
    LDA #$F0
    AND #$0F
assert reg.p 4
assert flags.n 0
assert flags.z 1

test and_imm_nzflag
    LDA #$FF
    AND #$F0
assert reg.p 4
assert flags.n 1
assert flags.z 0

test ora_imm_nzflag
    ORA #$00
assert reg.p 2
assert flags.n 0
assert flags.z 1

test ora_imm_nzflag
    ORA #$80
assert reg.p 2
assert flags.n 1
assert flags.z 0

test eor_imm_nzflag
    LDA #$70
    EOR #$70
assert reg.p 4
assert flags.n 0
assert flags.z 1

test eor_imm_nzflag
    LDA #$85
    EOR #$05
assert reg.p 4
assert flags.n 1
assert flags.z 0

test sbc_imm_nzflag
    LDA #$80
    SBC #$80
assert reg.p 4
assert flags.n 0
assert flags.z 1

test sbc_imm_nzflag
    LDA #$80
    SBC #$81
assert reg.p 4
assert flags.n 1
assert flags.z 0

test adc_imm_nzflag
    LDA #$80
    ADC #$80
assert reg.p 4
assert flags.n 0
assert flags.z 1

test adc_imm_nzflag
    LDA #$80
    ADC #$7F
assert reg.p 4
assert flags.n 1
assert flags.z 0
