#include "Mpu6502.h"
#include "Memory6502.h"
#include "exceptions.h"
#include "defines.h"
#include <sstream>
#include <fstream>
#include <iostream>

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
    int size = ifs.tellg();
    char *memblock = new char [size];
    ifs.seekg(0, std::iostream::beg);
    ifs.read(memblock, size);
    ifs.close();

    /* Then move the array buffer into the MPU's memory */
    for (int i = 0; i < size; ++i)
    {
        mem->set_byte(i, (uint8_t) memblock[i]);
    }

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

    switch (opcode)
    {
        /* LDA (8) {{{ */
        case 0xA9: // LDA IMM
            reg.ac = mem->get_immediate();
            set_nz_flags(reg.ac);
            reg.pc += 1;
            break;
        case 0xA5: // LDA ZERO
            reg.ac = mem->get_byte(mem->get_zero_page());
            set_nz_flags(reg.ac);
            reg.pc += 1;
            break;
        case 0xB5: // LDA ZERO X
            reg.ac = mem->get_byte(mem->get_zero_page_x());
            set_nz_flags(reg.ac);
            reg.pc += 1;
            break;
        case 0xAD: // LDA ABS
            reg.ac = mem->get_byte(mem->get_absolute());
            set_nz_flags(reg.ac);
            reg.pc += 2;
            break;
        case 0xBD: // LDA ABS X
            reg.ac = mem->get_byte(mem->get_absolute_x());
            set_nz_flags(reg.ac);
            reg.pc += 2;
            break;
        case 0xB9: // LDA ABS Y
            reg.ac = mem->get_byte(mem->get_absolute_y());
            set_nz_flags(reg.ac);
            reg.pc += 2;
            break;
        case 0xA1: // LDA IND X
            reg.ac = mem->get_byte(mem->get_indirect_x());
            set_nz_flags(reg.ac);
            reg.pc += 1;
            break;
        case 0xB1: // LDA IND Y
            reg.ac = mem->get_byte(mem->get_indirect_y());
            set_nz_flags(reg.ac);
            reg.pc += 1;
            break;
        /* }}} */
        /* LDX (5) {{{ */
        case 0xA2: // LDX IMM
            reg.x = mem->get_immediate();
            set_nz_flags(reg.x);
            reg.pc += 1;
            break;
        case 0xA6: // LDX ZERO
            reg.x = mem->get_byte(mem->get_zero_page());
            set_nz_flags(reg.x);
            reg.pc += 1;
            break;
        case 0xB6: // LDX ZERO Y
            reg.x = mem->get_byte(mem->get_zero_page_y());
            set_nz_flags(reg.x);
            reg.pc += 1;
            break;
        case 0xAE: // LDX ABS
            reg.x = mem->get_byte(mem->get_absolute());
            set_nz_flags(reg.x);
            reg.pc += 2;
            break;
        case 0xBE: // LDX ABS Y
            reg.x = mem->get_byte(mem->get_absolute_y());
            set_nz_flags(reg.x);
            reg.pc += 2;
            break;
        /* }}} */
        /* LDY (5) {{{ */
        case 0xA0: // LDY IMM
            reg.y = mem->get_immediate();
            set_nz_flags(reg.y);
            reg.pc += 1;
            break;
        case 0xA4: // LDY ZERO
            reg.y = mem->get_byte(mem->get_zero_page());
            set_nz_flags(reg.y);
            reg.pc += 1;
            break;
        case 0xB4: // LDY ZERO X
            reg.y = mem->get_byte(mem->get_zero_page_x());
            set_nz_flags(reg.y);
            reg.pc += 1;
            break;
        case 0xAC: // LDY ABS
            reg.y = mem->get_byte(mem->get_absolute());
            set_nz_flags(reg.y);
            reg.pc += 2;
            break;
        case 0xBC: // LDY ABS X
            reg.y = mem->get_byte(mem->get_absolute_x());
            set_nz_flags(reg.y);
            reg.pc += 2;
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
            set_nz_flags(reg.ac);
            reg.pc += 1;
            break;
        case 0x25: // AND ZERO
            reg.ac &= mem->get_byte(mem->get_zero_page());
            set_nz_flags(reg.ac);
            reg.pc += 1;
            break;
        case 0x35: // AND ZERO X
            reg.ac &= mem->get_byte(mem->get_zero_page_x());
            set_nz_flags(reg.ac);
            reg.pc += 1;
            break;
        case 0x2D: // AND ABS
            reg.ac &= mem->get_byte(mem->get_absolute());
            set_nz_flags(reg.ac);
            reg.pc += 2;
            break;
        case 0x3D: // AND ABS X
            reg.ac &= mem->get_byte(mem->get_absolute_x());
            set_nz_flags(reg.ac);
            reg.pc += 2;
            break;
        case 0x39: // AND ABS Y
            reg.ac &= mem->get_byte(mem->get_absolute_y());
            set_nz_flags(reg.ac);
            reg.pc += 2;
            break;
        case 0x21: // AND IND X
            reg.ac &= mem->get_byte(mem->get_indirect_x());
            set_nz_flags(reg.ac);
            reg.pc += 1;
            break;
        case 0x31: // AND IND Y
            reg.ac &= mem->get_byte(mem->get_indirect_y());
            set_nz_flags(reg.ac);
            reg.pc += 1;
            break;
        /* }}} */
        /* ORA (8) {{{ */
        case 0x09: // ORA IMM
            reg.ac |= mem->get_immediate();
            set_nz_flags(reg.ac);
            reg.pc += 1;
            break;
        case 0x05: // ORA ZERO
            reg.ac |= mem->get_byte(mem->get_zero_page());
            set_nz_flags(reg.ac);
            reg.pc += 1;
            break;
        case 0x15: // ORA ZERO X
            reg.ac |= mem->get_byte(mem->get_zero_page_x());
            set_nz_flags(reg.ac);
            reg.pc += 1;
            break;
        case 0x0D: // ORA ABS
            reg.ac |= mem->get_byte(mem->get_absolute());
            set_nz_flags(reg.ac);
            reg.pc += 2;
            break;
        case 0x1D: // ORA ABS X
            reg.ac |= mem->get_byte(mem->get_absolute_x());
            set_nz_flags(reg.ac);
            reg.pc += 2;
            break;
        case 0x19: // ORA ABS Y
            reg.ac |= mem->get_byte(mem->get_absolute_y());
            set_nz_flags(reg.ac);
            reg.pc += 2;
            break;
        case 0x01: // ORA IND X
            reg.ac |= mem->get_byte(mem->get_indirect_x());
            set_nz_flags(reg.ac);
            reg.pc += 1;
            break;
        case 0x11: // ORA IND Y
            reg.ac |= mem->get_byte(mem->get_indirect_y());
            set_nz_flags(reg.ac);
            reg.pc += 1;
            break;
        /* }}} */
        /* EOR (8) {{{ */
        case 0x49: // EOR IMM
            reg.ac ^= mem->get_immediate();
            set_nz_flags(reg.ac);
            reg.pc += 1;
            break;
        case 0x45: // EOR ZERO
            reg.ac ^= mem->get_byte(mem->get_zero_page());
            set_nz_flags(reg.ac);
            reg.pc += 1;
            break;
        case 0x55: // EOR ZERO X
            reg.ac ^= mem->get_byte(mem->get_zero_page_x());
            set_nz_flags(reg.ac);
            reg.pc += 1;
            break;
        case 0x4D: // EOR ABS
            reg.ac ^= mem->get_byte(mem->get_absolute());
            set_nz_flags(reg.ac);
            reg.pc += 2;
            break;
        case 0x5D: // EOR ABS X
            reg.ac ^= mem->get_byte(mem->get_absolute_x());
            set_nz_flags(reg.ac);
            reg.pc += 2;
            break;
        case 0x59: // EOR ABS Y
            reg.ac ^= mem->get_byte(mem->get_absolute_y());
            set_nz_flags(reg.ac);
            reg.pc += 2;
            break;
        case 0x41: // EOR IND X
            reg.ac ^= mem->get_byte(mem->get_indirect_x());
            set_nz_flags(reg.ac);
            reg.pc += 1;
            break;
        case 0x51: // EOR IND Y
            reg.ac ^= mem->get_byte(mem->get_indirect_y());
            set_nz_flags(reg.ac);
            reg.pc += 1;
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
