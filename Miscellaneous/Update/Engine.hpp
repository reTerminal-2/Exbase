/* Updated for version-080ad6451df24461 */

#pragma once

#include <Windows.h>
#include <iostream>
#include <vector>

#define REBASE(x) x + (uintptr_t)GetModuleHandle(nullptr)

struct lua_State;
struct Proto;

namespace Update {
    const uintptr_t RawScheduler = REBASE(0x625C3A8);

    const uintptr_t GetGlobalStateForInstance = REBASE(0xEBCDC0);
    const uintptr_t DecryptState = REBASE(0xC67700);

    const uintptr_t LuaVM__Load = REBASE(0xC6A290);
    const uintptr_t Task__Defer = REBASE(0x1097B70);

    namespace ExtraSpace {
        const uintptr_t Identity = 0x30;
        const uintptr_t Capabilities = 0x48;
        const uintptr_t Script = 0x50;
        const uintptr_t Actor = 0x58;
    }

    namespace TaskScheduler {
        const uintptr_t JobsStart = 0x1D0;
        const uintptr_t JobName = 0x90;
    }

    namespace ScriptContext {
        const uintptr_t GlobalState = 0x130;
        const uintptr_t DecryptState = 0x88;
    }

    namespace DataModel {
        const uintptr_t FakeDataModelPointer = REBASE(0x61A5F38);
        const uintptr_t FakeDataModelToDataModel = 0x1B8;

        const uintptr_t PlaceId = 0x178;
        const uintptr_t ScriptContext = 0x3C0;

        namespace Information {
            const uintptr_t ClassDescriptor = 0x18;
            const uintptr_t ClassName = 0x8;

            const uintptr_t Children = 0x78;
            const uintptr_t Parent = 0x10;
        }
    }
}

namespace RBX {
    using TGetGlobalStateForInstance = uintptr_t(__fastcall*)(uintptr_t, uintptr_t*, uintptr_t*);
    inline auto GetGlobalStateForInstance = (TGetGlobalStateForInstance)Update::GetGlobalStateForInstance;

    using TDecryptState = lua_State*(__fastcall*)(uintptr_t);
    inline auto DecryptState = (TDecryptState)Update::DecryptState;

    using TLuaVM__Load = int(__fastcall*)(lua_State*, void*, const char*, int);
    inline auto LuaVM__Load = (TLuaVM__Load)Update::LuaVM__Load;

    using TTask__Defer = int(__fastcall*)(lua_State*);
    inline auto Task__Defer = (TTask__Defer)Update::Task__Defer;

    inline __int64 GetThreadIdentity(uintptr_t L) {
        uintptr_t Userdata = *(uintptr_t*)(L + 0x78);
        return *(__int64*)(Userdata + Update::ExtraSpace::Identity);
    }

    inline void SetThreadIdentity(uintptr_t L, uintptr_t Identity) {
        uintptr_t Userdata = *(uintptr_t*)(L + 0x78);
        *(__int64*)(Userdata + Update::ExtraSpace::Identity) = Identity;
    }

    inline void SetThreadCapabilities(uintptr_t L, uintptr_t Capabilities) {
        uintptr_t Userdata = *(uintptr_t*)(L + 0x78);
        *(__int64*)(Userdata + Update::ExtraSpace::Capabilities) = Capabilities;
    }
}