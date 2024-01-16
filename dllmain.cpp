// Defines the entry point for the DLL application.
#include "pch.h"
#include <Minhook.h>
#include <Windows.h>
#include <cstdio>
#include <cstdint>
#include "hooks.h"

void init() {
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);

    MH_Initialize();

    setupFinishBattleHook();   
    setupStartBattleHook();
}

DWORD WINAPI mainThread(LPVOID) {
    init();
    printf("Cheat loaded!\n");

    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hModule);
        CreateThread(nullptr, 0, mainThread, hModule, 0, nullptr);
        break;
    case DLL_PROCESS_DETACH:
        MH_Uninitialize();
        FreeConsole();
        break;
    }
    return TRUE;
}