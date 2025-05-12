#pragma once

#include "common.h"
#include "bus.h"

constexpr u8 INT_VBLANK_ID = 0x00;
constexpr u8 INT_LCD_ID = 0x01;
constexpr u8 INT_TIMER_ID = 0x02;
constexpr u8 INT_SERIA_ID = 0x03;
constexpr u8 INT_JOYPAD_ID = 0x04;

class InterruptHandler {
   public:
    InterruptHandler(Bus& memBus);
    bool HasPending() const; // Check if there is at least one pending interrupt
    u8 GetNextPending(); // Get the next highest priority interrupt
    void ClearFlag(u8 id); // Clear the IF bit of the selected ID

    /* Getters */
    bool GetIME() const { return m_IME; }

    /* Setters */
    void SetIME(bool ime) { m_IME = ime; }

   private:
    bool m_IME;
    Bus& m_Bus;
};