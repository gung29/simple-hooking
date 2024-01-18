// dllmain.cpp : Defines the entry point for the DLL application.
#include "./minhook/minhook.h"
#include <Windows.h>
#include <cstdio>
#include <cstdint>
#include "hooks.h"

void init() {
    if (AllocConsole() == 0) {
        MessageBox(NULL, "Failed to allocate console", "Error", MB_ICONERROR);
        return;
    }

    FILE* f;
    if (freopen_s(&f, "CONOUT$", "w", stdout) != 0) {
        MessageBox(NULL, "Failed to redirect stdout", "Error", MB_ICONERROR);
        return;
    }

    if (MH_Initialize() != MH_OK) {
        MessageBox(NULL, "Failed to initialize MinHook", "Error", MB_ICONERROR);
        return;
    }

    setupFinishBattleHook();
    setupStartBattleHook();

    printf("Hack loaded!\n");
}

DWORD WINAPI mainThread(LPVOID) {
    init();

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