#include "Mpu6502.h"
#include "Memory6502.h"
#include "exceptions.h"
#include "defines.h"
#include <sstream>
#include <fstream>
#include <iostream>

/*
    *** IMPLEMENTED ***
    LDA, LDX, LDY, STA, STX, STY
    AND, ORA, EOR, TAX, TAY, TSX
    TXA, TXS, TYA, CLC, CLD, CLI,
    CLV, SEC, SED, SEI, BIT, NOP,
    ADC, SBC, CMP, CPX, CPY, 
    INC, INX INY, DEC, DEX, DEY,

    *: Needs tests

    *** NOT IMPLEMENTED ***
    PHA, PHP, PLA, PLP, RTI
    ASL, LSR
    ROL, ROR, JMP, JSR, RTS, BCC
    BCS, BEQ, BMI, BNE, BPL, BVC,
    BVS, BRK
*/

Mpu6502::Mpu6502() // {{{
{
    this->mem = new Memory6502(this);
    reset();
} // }}}
Mpu6502::~Mpu6502() // {{{
{
    delete mem;
} // }}}

void Mpu6502::load_binary_file(const std::string &filename) // {{{
{
    std::ifstream ifs(filename.c_str(), std::iostream::binary | std::iostream::ate);

    if (!ifs.is_open())
    {
        std::cerr << "Couldn't open file " << filename << std::endl;
        return;
    }

    /* Move the contents of the file into an array */
    mem->copy_from_istream(ifs);
    ifs.close();
} // }}}
void Mpu6502::reset() // {{{
{
    reg.x = 0;
    reg.y = 0;
    reg.ac = 0;
    reg.pc = 0;
    reg.ps = 0;
    reg.sp = 0xFF;

    mem->reset();
} // }}}
void Mpu6502::loop() // {{{
{
} // }}}
void Mpu6502::step() // {{{
{
    /* Fetch opcode and increment pc */
    uint8_t opcode = mem->get_byte(reg.pc);
    reg.pc += 1;

    uint8_t ubyte;
    uint16_t uword;
    switch (opcode)
    {
        /* LDA (8) {{{ */
        case 0xA9: // LDA IMM
            reg.ac = mem->get_immediate();
            goto op_lda_1;
        case 0xA5: // LDA ZERO
            reg.ac = mem->get_byte(mem->get_zero_page());
            goto op_lda_1;
        case 0xB5: // LDA ZERO X
            reg.ac = mem->get_byte(mem->get_zero_page_x());
            goto op_lda_1;
        case 0xAD: // LDA ABS
            reg.ac = mem->get_byte(mem->get_absolute());
            goto op_lda_2;
        case 0xBD: // LDA ABS X
            reg.ac = mem->get_byte(mem->get_absolute_x());
            goto op_lda_2;
        case 0xB9: // LDA ABS Y
            reg.ac = mem->get_byte(mem->get_absolute_y());
            goto op_lda_2;
        case 0xA1: // LDA IND X
            reg.ac = mem->get_byte(mem->get_indirect_x());
            goto op_lda_1;
        case 0xB1: // LDA IND Y
            reg.ac = mem->get_byte(mem->get_indirect_y());
            goto op_lda_1;
        op_lda_2:
            reg.pc += 1;
        op_lda_1:
            reg.pc += 1;
            set_nz_flags(reg.ac);
            break;
        /* }}} */
        /* LDX (5) {{{ */
        case 0xA2: // LDX IMM
            reg.x = mem->get_immediate();
            goto op_ldx_1;
        case 0xA6: // LDX ZERO
            reg.x = mem->get_byte(mem->get_zero_page());
            goto op_ldx_1;
        case 0xB6: // LDX ZERO Y
            reg.x = mem->get_byte(mem->get_zero_page_y());
            goto op_ldx_1;
        case 0xAE: // LDX ABS
            reg.x = mem->get_byte(mem->get_absolute());
            goto op_ldx_2;
        case 0xBE: // LDX ABS Y
            reg.x = mem->get_byte(mem->get_absolute_y());
            goto op_ldx_2;
        op_ldx_2:
            reg.pc += 1;
        op_ldx_1:
            reg.pc += 1;
            set_nz_flags(reg.x);
            break;
        /* }}} */
        /* LDY (5) {{{ */
        case 0xA0: // LDY IMM
            reg.y = mem->get_immediate();
            goto op_ldy_1;
        case 0xA4: // LDY ZERO
            reg.y = mem->get_byte(mem->get_zero_page());
            goto op_ldy_1;
        case 0xB4: // LDY ZERO X
            reg.y = mem->get_byte(mem->get_zero_page_x());
            goto op_ldy_1;
        case 0xAC: // LDY ABS
            reg.y = mem->get_byte(mem->get_absolute());
            goto op_ldy_2;
        case 0xBC: // LDY ABS X
            reg.y = mem->get_byte(mem->get_absolute_x());
            goto op_ldy_2;
        op_ldy_2:
            reg.pc += 1;
        op_ldy_1:
            reg.pc += 1;
            set_nz_flags(reg.y);
            break;
        /* }}} */
        /* STA (7) {{{ */
        case 0x85: // STA ZERO
            mem->set_byte(mem->get_zero_page(), reg.ac);
            reg.pc += 1;
            break;
        case 0x95: // STA ZERO X
            mem->set_byte(mem->get_zero_page_x(), reg.ac);
            reg.pc += 1;
            break;
        case 0x8D: // STA ABS
            mem->set_byte(mem->get_absolute(), reg.ac);
            reg.pc += 2;
            break;
        case 0x9D: // STA ABS X
            mem->set_byte(mem->get_absolute_x(), reg.ac);
            reg.pc += 2;
            break;
        case 0x99: // STA ABS Y
            mem->set_byte(mem->get_absolute_y(), reg.ac);
            reg.pc += 2;
            break;
        case 0x81: // STA IND X
            mem->set_byte(mem->get_indirect_x(), reg.ac);
            reg.pc += 1;
            break;
        case 0x91: // STA IND Y
            mem->set_byte(mem->get_indirect_y(), reg.ac);
            reg.pc += 1;
            break;
        /* }}} */
        /* STX (3) {{{ */
        case 0x86: // STX ZERO
            mem->set_byte(mem->get_zero_page(), reg.x);
            reg.pc += 1;
            break;
        case 0x96: // STX ZERO Y
            mem->set_byte(mem->get_zero_page_y(), reg.x);
            reg.pc += 1;
            break;
        case 0x8E: // STX ABS
            mem->set_byte(mem->get_absolute(), reg.x);
            reg.pc += 2;
            break;
        /* }}} */
        /* STY (3) {{{ */
        case 0x84: // STY ZERO
            mem->set_byte(mem->get_zero_page(), reg.y);
            reg.pc += 1;
            break;
        case 0x94: // STY ZERO X
            mem->set_byte(mem->get_zero_page_x(), reg.y);
            reg.pc += 1;
            break;
        case 0x8C: // STY ABS
            mem->set_byte(mem->get_absolute(), reg.y);
            reg.pc += 2;
            break;
        /* }}} */
        /* AND (8) {{{ */
        case 0x29: // AND IMM
            reg.ac &= mem->get_immediate();
            goto op_and_1;
        case 0x25: // AND ZERO
            reg.ac &= mem->get_byte(mem->get_zero_page());
            goto op_and_1;
        case 0x35: // AND ZERO X
            reg.ac &= mem->get_byte(mem->get_zero_page_x());
            goto op_and_1;
        case 0x2D: // AND ABS
            reg.ac &= mem->get_byte(mem->get_absolute());
            goto op_and_2;
        case 0x3D: // AND ABS X
            reg.ac &= mem->get_byte(mem->get_absolute_x());
            goto op_and_2;
        case 0x39: // AND ABS Y
            reg.ac &= mem->get_byte(mem->get_absolute_y());
            goto op_and_2;
        case 0x21: // AND IND X
            reg.ac &= mem->get_byte(mem->get_indirect_x());
            goto op_and_1;
        case 0x31: // AND IND Y
            reg.ac &= mem->get_byte(mem->get_indirect_y());
            goto op_and_1;
        op_and_2:
            reg.pc += 1;
        op_and_1:
            reg.pc += 1;
            set_nz_flags(reg.ac);
            break;
        /* }}} */
        /* ORA (8) {{{ */
        case 0x09: // ORA IMM
            reg.ac |= mem->get_immediate();
            goto op_ora_1;
        case 0x05: // ORA ZERO
            reg.ac |= mem->get_byte(mem->get_zero_page());
            goto op_ora_1;
        case 0x15: // ORA ZERO X
            reg.ac |= mem->get_byte(mem->get_zero_page_x());
            goto op_ora_1;
        case 0x0D: // ORA ABS
            reg.ac |= mem->get_byte(mem->get_absolute());
            goto op_ora_2;
        case 0x1D: // ORA ABS X
            reg.ac |= mem->get_byte(mem->get_absolute_x());
            goto op_ora_2;
        case 0x19: // ORA ABS Y
            reg.ac |= mem->get_byte(mem->get_absolute_y());
            goto op_ora_2;
        case 0x01: // ORA IND X
            reg.ac |= mem->get_byte(mem->get_indirect_x());
            goto op_ora_1;
        case 0x11: // ORA IND Y
            reg.ac |= mem->get_byte(mem->get_indirect_y());
            goto op_ora_1;
        op_ora_2:
            reg.pc += 1;
        op_ora_1:
            reg.pc += 1;
            set_nz_flags(reg.ac);
            break;
        /* }}} */
        /* EOR (8) {{{ */
        case 0x49: // EOR IMM
            reg.ac ^= mem->get_immediate();
            goto op_eor_1;
        case 0x45: // EOR ZERO
            reg.ac ^= mem->get_byte(mem->get_zero_page());
            goto op_eor_1;
        case 0x55: // EOR ZERO X
            reg.ac ^= mem->get_byte(mem->get_zero_page_x());
            goto op_eor_1;
        case 0x4D: // EOR ABS
            reg.ac ^= mem->get_byte(mem->get_absolute());
            goto op_eor_2;
        case 0x5D: // EOR ABS X
            reg.ac ^= mem->get_byte(mem->get_absolute_x());
            goto op_eor_2;
        case 0x59: // EOR ABS Y
            reg.ac ^= mem->get_byte(mem->get_absolute_y());
            goto op_eor_2;
        case 0x41: // EOR IND X
            reg.ac ^= mem->get_byte(mem->get_indirect_x());
            goto op_eor_1;
        case 0x51: // EOR IND Y
            reg.ac ^= mem->get_byte(mem->get_indirect_y());
            goto op_eor_1;
        op_eor_2:
            reg.pc += 1;
        op_eor_1:
            reg.pc += 1;
            set_nz_flags(reg.ac);
            break;
        /* }}} */
        /* BIT (2) {{{ */
        case 0x24: // BIT ZERO
            ubyte = mem->get_byte(mem->get_zero_page());
            goto bit_op;
        case 0x2C: // BIT ABS
            ubyte = mem->get_byte(mem->get_absolute());
            reg.pc += 1;
        bit_op:
            reg.pc += 1;
            reg.ps[FLAG_ZERO] = 0 == (ubyte & reg.ac);
            reg.ps[FLAG_NEGATIVE] = ((int8_t) ubyte) < 0;
            reg.ps[FLAG_OVERFLOW] = (ubyte & (1 << 6)) ? 1 : 0;
            break;
        /* }}} */
        /* ADC (8) {{{ */
        case 0x69: // ADC IMM
            ubyte = mem->get_immediate();
            goto adc_op_1;
        case 0x65: // ADC ZERO
            ubyte = mem->get_byte(mem->get_zero_page());
            goto adc_op_1;
        case 0x75: // ADC ZERO X
            ubyte = mem->get_byte(mem->get_zero_page_x());
            goto adc_op_1;
        case 0x6D: // ADC ABS
            ubyte = mem->get_byte(mem->get_absolute());
            goto adc_op_2;
        case 0x7D: // ADC ABS X
            ubyte = mem->get_byte(mem->get_absolute_x());
            goto adc_op_2;
        case 0x79: // ADC ABS Y
            ubyte = mem->get_byte(mem->get_absolute_y());
            goto adc_op_2;
        case 0x61: // ADC IND X
            ubyte = mem->get_byte(mem->get_indirect_x());
            goto adc_op_1;
        case 0x71: // ADC IND Y
            ubyte = mem->get_byte(mem->get_indirect_y());
            goto adc_op_1;

        adc_op_2:
            reg.pc += 1;
        adc_op_1:
            reg.pc += 1;

            uword = reg.ac + ubyte;
            if (reg.ps[FLAG_CARRY])
                uword += 1;

            if (uword > 0xFF)
                reg.ps[FLAG_CARRY] = 1;
            else
                reg.ps[FLAG_CARRY] = 0;

            if ((int8_t)reg.ac + (int8_t)ubyte > 0x7f || (int8_t)reg.ac + (int8_t)ubyte < -0x80)
                reg.ps[FLAG_OVERFLOW] = 1;
            else
                reg.ps[FLAG_OVERFLOW] = 0;

            reg.ac = uword;
            set_nz_flags(reg.ac);
            break;
        /* }}} */
        /* SBC (8) {{{ */
        case 0xE9: // SBC IMM
            ubyte = mem->get_immediate();
            goto sbc_op_1;
        case 0xE5: // SBC ZERO
            ubyte = mem->get_byte(mem->get_zero_page());
            goto sbc_op_1;
        case 0xF5: // SBC ZERO X
            ubyte = mem->get_byte(mem->get_zero_page_x());
            goto sbc_op_1;
        case 0xED: // SBC ABS
            ubyte = mem->get_byte(mem->get_absolute());
            goto sbc_op_2;
        case 0xFD: // SBC ABS X
            ubyte = mem->get_byte(mem->get_absolute_x());
            goto sbc_op_2;
        case 0xF9: // SBC ABS Y
            ubyte = mem->get_byte(mem->get_absolute_y());
            goto sbc_op_2;
        case 0xE1: // SBC IND X
            ubyte = mem->get_byte(mem->get_indirect_x());
            goto sbc_op_1;
        case 0xF1: // SBC IND Y
            ubyte = mem->get_byte(mem->get_indirect_y());
            goto sbc_op_1;

        sbc_op_2:
            reg.pc += 1;
        sbc_op_1:
            reg.pc += 1;

            uword = reg.ac - ubyte;
            if (reg.ps[FLAG_CARRY])
                uword -= 1;

            if (uword < 0x100)
                reg.ps[FLAG_CARRY] = 1;
            else
                reg.ps[FLAG_CARRY] = 0;

            if ((int8_t)reg.ac - (int8_t)ubyte > 0x7f || (int8_t)reg.ac - (int8_t)ubyte < -0x80)
                reg.ps[FLAG_OVERFLOW] = 1;
            else
                reg.ps[FLAG_OVERFLOW] = 0;

            reg.ac = uword;
            set_nz_flags(reg.ac);
            break;
        /* }}} */
        /* CMP (8) {{{ */
        case 0xC9: // CMP IMM
            ubyte = mem->get_immediate();
            goto cmp_op_1;
        case 0xC5: // CMP ZERO
            ubyte = mem->get_byte(mem->get_zero_page());
            goto cmp_op_1;
        case 0xD5: // CMP ZERO X
            ubyte = mem->get_byte(mem->get_zero_page_x());
            goto cmp_op_1;
        case 0xCD: // CMP ABS
            ubyte = mem->get_byte(mem->get_absolute());
            goto cmp_op_2;
        case 0xDD: // CMP ABS X
            ubyte = mem->get_byte(mem->get_absolute_x());
            goto cmp_op_2;
        case 0xD9: // CMP ABS Y
            ubyte = mem->get_byte(mem->get_absolute_y());
            goto cmp_op_2;
        case 0xC1: // CMP IND X
            ubyte = mem->get_byte(mem->get_indirect_x());
            goto cmp_op_1;
        case 0xD1: // CMP IND Y
            ubyte = mem->get_byte(mem->get_indirect_y());
            goto cmp_op_1;

        cmp_op_2:
            reg.pc += 1;
        cmp_op_1:
            reg.pc += 1;

            reg.ps[FLAG_CARRY] = (reg.ac >= ubyte);
            set_nz_flags(reg.ac - ubyte);
            break;
        /* }}} */
        /* CPX (3) {{{ */
        case 0xE0: // CPX IMM
            ubyte = mem->get_immediate();
            goto cpx_op_1;
        case 0xE4: // CPX ZERO
            ubyte = mem->get_byte(mem->get_zero_page());
            goto cpx_op_1;
        case 0xEC: // CPX ABS
            ubyte = mem->get_byte(mem->get_absolute());
            reg.pc += 1;

        cpx_op_1:
            reg.pc += 1;

            reg.ps[FLAG_CARRY] = (reg.x >= ubyte);
            set_nz_flags(reg.x - ubyte);
            break;
        /* }}} */
        /* CPY (3) {{{ */
        case 0xC0: // CPY IMM
            ubyte = mem->get_immediate();
            goto cpy_op_1;
        case 0xC4: // CPY ZERO
            ubyte = mem->get_byte(mem->get_zero_page());
            goto cpy_op_1;
        case 0xCC: // CPY ABS
            ubyte = mem->get_byte(mem->get_absolute());
            reg.pc += 1;

        cpy_op_1:
            reg.pc += 1;

            reg.ps[FLAG_CARRY] = (reg.y >= ubyte);
            set_nz_flags(reg.y - ubyte);
            break;
        /* }}} */
        /* INC (4) {{{ */
        case 0xE6: // INC ZERO
            uword = mem->get_zero_page();
            goto inc_op_1;
        case 0xF6: // INC ZERO X
            uword = mem->get_zero_page_x();
            goto inc_op_1;
        case 0xEE: // INC ABS
            uword = mem->get_absolute();
            goto inc_op_2;
        case 0xFE: // INC ABS X
            uword = mem->get_absolute_x();
            goto inc_op_2;

        inc_op_2:
            reg.pc += 1;
        inc_op_1:
            reg.pc += 1;

            mem->set_byte(uword, mem->get_byte(uword) + 1);
            set_nz_flags(mem->get_byte(uword));
            break;
        /* }}} */
        /* DEC (4) {{{ */
        case 0xC6: // DEC ZERO
            uword = mem->get_zero_page();
            goto dec_op_1;
        case 0xd6: // DEC ZERO X
            uword = mem->get_zero_page_x();
            goto dec_op_1;
        case 0xCE: // DEC ABS
            uword = mem->get_absolute();
            goto dec_op_2;
        case 0xDE: // DEC ABS X
            uword = mem->get_absolute_x();
            goto dec_op_2;

        dec_op_2:
            reg.pc += 1;
        dec_op_1:
            reg.pc += 1;

            mem->set_byte(uword, mem->get_byte(uword) - 1);
            set_nz_flags(mem->get_byte(uword));
            break;
        /* }}} */
        /* INX (1) {{{ */
        case 0xE8: // INX IMPLIED
            reg.x += 1;
            set_nz_flags(reg.x);
            break;
        /* }}} */
        /* DEX (1) {{{ */
        case 0xCA: // DEX IMPLIED
            reg.x -= 1;
            set_nz_flags(reg.x);
            break;
        /* }}} */
        /* INY (1) {{{ */
        case 0xC8: // INY IMPLIED
            reg.y += 1;
            set_nz_flags(reg.y);
            break;
        /* }}} */
        /* DEY (1) {{{ */
        case 0x88: // DEY IMPLIED
            reg.y -= 1;
            set_nz_flags(reg.y);
            break;
        /* }}} */
        /* TAX (1) {{{ */
        case 0xAA:
            reg.x = reg.ac;
            set_nz_flags(reg.x);
            break;
        /* }}} */
        /* TAY (1) {{{ */
        case 0xA8:
            reg.y = reg.ac;
            set_nz_flags(reg.y);
            break;
        /* }}} */
        /* TSX (1) {{{ */
        case 0xBA:
            reg.x = reg.sp;
            set_nz_flags(reg.x);
            break;
        /* }}} */
        /* TXA (1) {{{ */
        case 0x8A:
            reg.ac = reg.x;
            set_nz_flags(reg.ac);
            break;
        /* }}} */
        /* TXS (1) {{{ */
        case 0x9A:
            reg.sp = reg.x;
            set_nz_flags(reg.sp);
            break;
        /* }}} */
        /* TYA (1) {{{ */
        case 0x98:
            reg.ac = reg.y;
            set_nz_flags(reg.ac);
            break;
        /* }}} */
        /* CLC (1) {{{ */
        case 0x18:
            reg.ps[FLAG_CARRY] = 0;
            break;
        /* }}} */
        /* CLD (1) {{{ */
        case 0xD8:
            reg.ps[FLAG_DECIMAL] = 0;
            break;
        /* }}} */
        /* CLI (1) {{{ */
        case 0x58:
            reg.ps[FLAG_INTERRUPT] = 0;
            break;
        /* }}} */
        /* CLV (1) {{{ */
        case 0xB8:
            reg.ps[FLAG_OVERFLOW] = 0;
            break;
        /* }}} */
        /* SEC (1) {{{ */
        case 0x38:
            reg.ps[FLAG_CARRY] = 1;
            break;
        /* }}} */
        /* SED (1) {{{ */
        case 0xF8:
            reg.ps[FLAG_DECIMAL] = 1;
            break;
        /* }}} */
        /* SEI (1) {{{ */
        case 0x78:
            reg.ps[FLAG_INTERRUPT] = 1;
            break;
        /* }}} */
        /* NOP (1) {{{ */
        case 0xEA:
            break;
        /* }}} */
        default:
            throw InvalidOpcodeException(opcode);
    }
} // }}}

std::string Mpu6502::to_string() const // {{{
{
    std::stringstream ss;

    ss << "<mpu6502 " << this;
    ss << " PC:" << (uint16_t) reg.pc;
    ss << " PS:" << reg.ps;
    ss << " SP:" << (uint16_t) reg.sp;
    ss << " AC:" << (uint16_t) reg.ac;
    ss << " X:"  << (uint16_t) reg.x;
    ss << " Y:"  << (uint16_t) reg.y << '>';

    return ss.str();
} // }}}

#if 0
const int Mpu6502::op_cycles[] = { // {{{
    7, 6, 0, 0, 0, 3, 5, 0, 3, 2, 2, 0, 0, 4, 6, 0,  // 00
    2, 5, 0, 0, 0, 4, 6, 0, 2, 4, 0, 0, 0, 4, 7, 0,  // 10
    6, 6, 0, 0, 3, 3, 5, 0, 4, 2, 2, 0, 4, 4, 6, 0,  // 20
    2, 5, 0, 0, 0, 4, 6, 0, 2, 4, 0, 0, 0, 4, 7, 0,  // 30
    6, 6, 0, 0, 0, 3, 5, 0, 3, 2, 2, 0, 3, 4, 6, 0,  // 40
    2, 5, 0, 0, 0, 4, 6, 0, 2, 4, 0, 0, 0, 4, 7, 0,  // 50
    6, 6, 0, 0, 0, 3, 5, 0, 4, 2, 2, 0, 5, 4, 6, 0,  // 60
    2, 5, 0, 0, 0, 4, 6, 0, 2, 4, 0, 0, 0, 4, 7, 0,  // 70
    0, 6, 0, 0, 3, 3, 3, 0, 2, 0, 2, 0, 4, 4, 4, 0,  // 80
    2, 6, 0, 0, 4, 4, 4, 0, 2, 5, 2, 0, 0, 5, 0, 0,  // 90
    2, 6, 2, 0, 3, 3, 3, 0, 2, 2, 2, 0, 4, 4, 4, 0,  // A0
    2, 5, 0, 0, 4, 4, 4, 0, 2, 4, 2, 0, 4, 4, 4, 0,  // B0
    2, 6, 0, 0, 3, 3, 5, 0, 2, 2, 2, 0, 4, 4, 3, 0,  // C0
    2, 5, 0, 0, 0, 4, 6, 0, 2, 4, 0, 0, 0, 4, 7, 0,  // D0
    2, 6, 0, 0, 3, 3, 5, 0, 2, 2, 2, 0, 4, 4, 6, 0,  // E0
    2, 5, 0, 0, 0, 4, 6, 0, 2, 4, 0, 0, 0, 4, 7, 0   // F0
}; // }}}
#endif
