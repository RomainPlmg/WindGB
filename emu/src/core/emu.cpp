#include "emu.h"

#include <atomic>
#include <csignal>

#include "bus.h"
#include "cartridge.h"
#include "cpu.h"
#include "utils/exit_codes.h"
#include "utils/log.h"

std::atomic<bool> g_ExitRequested = false;
std::atomic<int> g_ExitSignal{0};

Gameboy::Gameboy(Cartridge& cartridge) : m_Cartridge(cartridge) {
    std::signal(SIGINT, signal_callback_handler);  // Register signal and signal handler

    m_Bus = std::make_unique<Bus>();
    m_IO = std::make_unique<IO>(*m_Bus);
    m_Bus->Attach(m_IO.get());
    m_Bus->Attach(&m_Cartridge);

    m_PPU = std::make_unique<PPU>(*m_Bus);
    m_CPU = std::make_unique<CPU>(*m_Bus, *m_PPU, *m_IO);
}

void Gameboy::Init() {
    m_Running = true;
    m_CPU->Reset();  // Reset the CPU at the initial state
    m_IO->Reset();
    m_PPU->Init();
}

void Gameboy::Step() {
    if (g_ExitRequested) {
        HandleAsyncExit();
    }

    u8 cycles = m_CPU->Step();  // Step in the CPU & recover nb of T-Cycles
}

std::string_view Gameboy::GetLoadedGame() const {
    std::string_view title = m_Cartridge.GetContext().header->GetTitle();
    return title;
}

void Gameboy::VerboseLog(bool enable) {
    if (enable)
        Log::Get()->set_level(spdlog::level::debug);
    else
        Log::Get()->set_level(spdlog::level::info);
}

void Gameboy::InitLog() { Log::Init(); }

void Gameboy::HandleAsyncExit() {
    LOG_INFO("Caught signal '{}'", g_ExitSignal.load());
    Log::Get()->flush();
    spdlog::shutdown();

    std::exit(g_ExitSignal.load());
}

void Gameboy::signal_callback_handler(int signum) {
    g_ExitRequested = true;
    g_ExitSignal = signum;
}