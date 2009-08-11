test lda_imm_nflag
    LDA #$AB
assert flags.n 1
assert flags.z 0

test lda_imm_zflag
    LDA #$AB
    LDA #0
assert flags.n 0
assert flags.z 1

test lda_imm_nzflag
    LDA #$a
assert flags.n 0
assert flags.z 0

test ldx_imm_nflag
    LDX #$AB
assert flags.n 1
assert flags.z 0

test ldx_imm_zflag
    LDX #$AB
    LDX #0
assert flags.n 0
assert flags.z 1

test ldx_imm_nzflag
    LDX #$A
assert flags.n 0
assert flags.z 0

test ldy_imm_nflag
    LDY #$AB
assert flags.n 1
assert flags.z 0

test ldy_imm_zflag
    LDY #$AB
    LDY #0
assert flags.n 0
assert flags.z 1

test ldy_imm_nzflag
    LDY #$A
assert flags.n 0
assert flags.z 0
