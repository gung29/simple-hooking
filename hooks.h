#pragma once
#include "offsets.h"
#include <Windows.h>
#include <cstdio>
#include <string>
#include <iostream>

using namespace std;

// Function pointers for the original functions
void(__fastcall *FinishBattleFunc)(DWORD *__this, DWORD*);
void(__fastcall *StartBattleFunc)(DWORD *__this, DWORD*);

// Hook function for startBattle
void __fastcall StartBattle_hook(DWORD *__this, DWORD *method) {
    // Call the original startBattle function
    StartBattleFunc(__this, method);

    // Call the finishBattle function
    cout << "Starting battle, finishing immediately..." << endl;
    FinishBattleFunc(__this, method);
}

// Hook function for finishBattle
void __fastcall FinishBattle_hook(DWORD *__this, DWORD *method) {
    // Call the original function
    FinishBattleFunc(__this, method);
}

// Function to set up the finishBattle hook
void setupFinishBattleHook() {
    MH_CreateHook(reinterpret_cast<LPVOID>(gameAssembly + finishBattle), &FinishBattle_hook, (LPVOID *)&FinishBattleFunc);
    MH_EnableHook(reinterpret_cast<LPVOID>(gameAssembly + finishBattle));
}

// Function to set up the startBattle hook
void setupStartBattleHook() {
    MH_CreateHook(reinterpret_cast<LPVOID>(gameAssembly + startBattle), &StartBattle_hook, (LPVOID *)&StartBattleFunc);
    MH_EnableHook(reinterpret_cast<LPVOID>(gameAssembly + startBattle));
}