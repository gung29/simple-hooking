#pragma once
#include "offsets.h"
#include <Windows.h>
#include <cstdio>
#include <string>
#include <iostream>

using namespace std;

// Function pointers for the original functions
void(__fastcall *SetDamageToTargetFunc)(DWORD *__this, int64_t, DWORD*, DWORD*);
void(__fastcall *FinishBattleFunc)(DWORD *__this, DWORD*);
void(__fastcall *StartBattleFunc)(DWORD *__this, DWORD*);

// Hook function for StartBattle
void __fastcall StartBattle_hook(DWORD *__this, DWORD *method) {
    // Call the original StartBattle function
    StartBattleFunc(__this, method);

    // Call the finish_battle function
    cout << "Starting battle, finishing immediately..." << endl;
    FinishBattleFunc(__this, method);
    // This will finish the battle immediately after it starts
}

// Hook function for FinishBattle (finish_battle)
void __fastcall FinishBattle_hook(DWORD *__this, DWORD *method) {
    // Call the original FGMHOGHMLBG function
    FinishBattleFunc(__this, method);
}

// Function to set up the FinishBattle (finish_battle) hook
void setupFinishBattleHook() {
    MH_CreateHook(reinterpret_cast<LPVOID>(gameAssembly + finish_battle), &FinishBattle_hook, (LPVOID *)&FinishBattleFunc);
    MH_EnableHook(reinterpret_cast<LPVOID>(gameAssembly + finish_battle));
}

// Function to set up the StartBattle hook
void setupStartBattleHook() {
    MH_CreateHook(reinterpret_cast<LPVOID>(gameAssembly + start_battle), &StartBattle_hook, (LPVOID *)&StartBattleFunc);
    MH_EnableHook(reinterpret_cast<LPVOID>(gameAssembly + start_battle));
}

