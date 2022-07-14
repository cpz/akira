#include <Windows.h>
#include <thread>
#include <format>

#include <include/MinHook.h>

using GetSystemPowerStatusFn = bool(WINAPI*)(bool*, unsigned __int8*, bool);
GetSystemPowerStatusFn fn = nullptr;

int increment = 0;

bool CheckPowerStatus(bool*, unsigned __int8*, bool)
{
    return true;
}

void OnImageLoad()
{
    void* check_power_status = GetProcAddress(GetModuleHandleA("iscflash.dll"), "?CheckPowerStatus@@YA_NAA_NAAE_N@Z");

    if (MH_Initialize() != MH_OK)
    {
        MessageBoxA(nullptr, "Cannot initialize min hook!", nullptr, 0);
        return;
    }


    if (MH_CreateHook(check_power_status, &CheckPowerStatus,
                      reinterpret_cast<LPVOID*>(&fn)) != MH_OK)
    {
        MessageBoxA(nullptr, "Cannot create hook for CheckPowerStatus!", nullptr, 0);
        return;
    }

    if (MH_EnableHook(check_power_status) != MH_OK)
    {
        MessageBoxA(nullptr, "Cannot enable hook for CheckPowerStatus!", nullptr, 0);
        return;
    }
}

BOOL APIENTRY DllEntryPoint(const HMODULE module,
                            const DWORD ul_reason_for_call,
                            [[maybe_unused]] LPVOID reserved
)
{
    DisableThreadLibraryCalls(module);

    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        std::thread(OnImageLoad).detach();
        break;
    default:
        break;
    }
    return TRUE;
}
