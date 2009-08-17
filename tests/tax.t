test tax_1
    LDA #$AB
    TAX
assert reg.p 3
assert reg.x 0xAB
