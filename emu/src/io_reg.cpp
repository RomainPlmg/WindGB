#include "io_reg.h"

#include "log.h"

u8 IO::Read(u16 addr) const {
    u16 relativeAddr = addr - IO_REG_START;
    if (relativeAddr >= IO_REG_SIZE) {
        LOG_ERROR("Address addr 0x{:02X} is out of IO REG range 0x{:02X}<->0x{:02X}", addr, IO_REG_START, IO_REG_START + IO_REG_SIZE - 1);
        return 0;
    }
    return m_Data.at(relativeAddr);
}

void IO::Write(u16 addr, u8 data) {
    u16 relativeAddr = addr - IO_REG_START;
    if (relativeAddr >= IO_REG_SIZE) {
        LOG_ERROR("Address addr 0x{:02X} is out of IO REG range 0x{:02X}<->0x{:02X}", addr, IO_REG_START, IO_REG_START + IO_REG_SIZE - 1);
        return;
    }

    m_Data[relativeAddr] = data;
}
