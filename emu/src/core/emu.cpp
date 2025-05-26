#include "emu.h"

#include <argparse/argparse.hpp>
#include <atomic>
#include <csignal>

#include "bus.h"
#include "cartridge.h"
#include "cpu.h"
#include "utils/exit_codes.h"
#include "utils/log.h"

std::atomic<bool> g_ExitRequested = false;
std::atomic<int> g_ExitSignal{0};

Gameboy::Gameboy(int argc, char const* argv[]) {
    std::signal(SIGINT, signal_callback_handler);  // Register signal and signal handler

    std::string romPath = {};
    std::string outputFile = {};
    bool debug = false;
    bool gbd = false;
    bool header = false;

    argparse::ArgumentParser parser("WindGB", "0.1.0");
    parser.add_argument("rom_path").help("Path to the ROM to load into the emulator.").store_into(romPath);
    parser.add_argument("-d", "--debug").default_value(false).implicit_value(true).help("Enable standard logging").store_into(debug);
    parser.add_argument("--header").default_value(false).implicit_value(true).help("Only print the header of the ROM").store_into(header);
    parser.add_argument("--gameboy_doctor")
        .default_value(false)
        .implicit_value(true)
        .help("Enable logging for Gameboy Doctor tests. (Disable the standard logging)")
        .store_into(gbd);
    parser.add_argument("-o", "--output").help("Log output file.").store_into(outputFile);
    try {
        parser.parse_args(argc, argv);
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        std::cerr << parser;
        exit(EXIT_INVALID_ARGS);
    }

    Log::Init(outputFile);
    Log::InitDoctor(outputFile);

    if (gbd) {
        Log::Disable();
    } else if (debug || header) {
        Log::DisableDoctor();
    } else {
        Log::Disable();
        Log::DisableDoctor();
    }

    m_Cartridge = std::make_unique<Cartridge>();
    m_Bus = std::make_unique<Bus>(m_Cartridge.get());
    m_CPU = std::make_unique<CPU>(*m_Bus);
    m_PPU = std::make_unique<PPU>(*m_Bus);

    if (argc < 2) {
        LOG_CRITICAL("You need to specify a binary to load");
        exit(EXIT_INVALID_ARGS);
    }

    m_Cartridge->Load(romPath);
    if (header) exit(EXIT_OK);
}

void Gameboy::Init() {
    m_CPU->Reset();  // Reset the CPU at the initial state
}

void Gameboy::Step() {
    if (g_ExitRequested) {
        HandleAsyncExit();
    }

    u8 cycles = m_CPU->Step(); // Step in the CPU & recover nb of T-Cycles
    m_PPU->Step(cycles);
}

std::string_view Gameboy::GetLoadedGame() const {
    std::string_view title = m_Cartridge->GetContext().header->GetTitle();
    return title;
}

void Gameboy::HandleAsyncExit() {
    LOG_INFO("Caught signal '{}'", g_ExitSignal.load());
    Log::Get()->flush();
    Log::GetDoctor()->flush();
    spdlog::shutdown();

    std::exit(g_ExitSignal.load());
}

void Gameboy::signal_callback_handler(int signum) {
    g_ExitRequested = true;
    g_ExitSignal = signum;
}