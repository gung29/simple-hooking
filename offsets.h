#pragma once

uintptr_t gameAssembly = (uintptr_t)GetModuleHandleA("GameAssembly.dll");
// Find the offsets manually, then put them here
constexpr uintptr_t finish_battle = 0x000000;
constexpr uintptr_t start_battle = 0x000000;