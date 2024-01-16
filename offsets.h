#pragma once

// Fill in the offsets here
uintptr_t gameAssembly = (uintptr_t)GetModuleHandleA("GameAssembly.dll");
constexpr uintptr_t damage = 0x000000;
constexpr uintptr_t finishBattle = 0x000000;
constexpr uintptr_t startBattle = 0x000000;