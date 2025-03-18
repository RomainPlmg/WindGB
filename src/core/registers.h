#ifndef __REGISTERS_H__
#define __REGISTERS_H__

#include <cstdint>

class Registers {
   public:
    /* Getters */
    inline uint8_t GetA() const { return m_A; }
    inline uint8_t GetB() const { return m_B; }
    inline uint8_t GetC() const { return m_C; }
    inline uint8_t GetD() const { return m_D; }
    inline uint8_t GetE() const { return m_E; }
    // inline uint8_t GetF() const { return m_F; } // Strange behavior so excluded from getters
    inline uint8_t GetH() const { return m_H; }
    inline uint8_t GetL() const { return m_L; }
    inline uint16_t GetSP() const { return m_SP; }
    inline uint16_t GetPC() const { return m_PC; }

    /* Setters */
    inline void SetA(uint8_t value) { m_A = value; }
    inline void SetB(uint8_t value) { m_B = value; }
    inline void SetC(uint8_t value) { m_C = value; }
    inline void SetD(uint8_t value) { m_D = value; }
    inline void SetE(uint8_t value) { m_E = value; }
    // inline void SetF(uint8_t value) { m_F = value; } // Strange behavior so excluded from setters
    inline void SetH(uint8_t value) { m_H = value; }
    inline void SetL(uint8_t value) { m_L = value; }
    inline void SetSP(uint16_t value) { m_SP = value; }
    inline void SetPC(uint16_t value) { m_PC = value; }

   private:
    uint8_t m_A = 0;
    uint8_t m_B = 0;
    uint8_t m_C = 0;
    uint8_t m_D = 0;
    uint8_t m_E = 0;
    uint8_t m_F = 0;
    uint8_t m_H = 0;
    uint8_t m_L = 0;
    uint16_t m_SP = 0;
    uint16_t m_PC = 0;
};

#endif  // __REGISTERS_H__