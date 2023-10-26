#include <thread>
#include <include/MinHook.h>

namespace
{
    using namespace std::literals;

    constexpr auto kAkiraCaption = "akira"sv;
}

int MsgBox(const std::string_view msg, const std::optional<std::uint32_t> type = std::nullopt)
{
    return MessageBoxA(nullptr, msg.data(), kAkiraCaption.data(), type.value_or(MB_OK));
}

// a2 leads to bios data structures
class InsydeFlash
{
public:
    std::string_view GetID()
    {
        if (!m_id_) return {};
        return { m_id_ };
    }

    std::string_view GetVersion()
    {
        if (!m_version_) return {};
        return { m_version_ };
    }

    [[nodiscard]] auto GetBatteryValue() const { return m_battery_value_; }
    void SetBatteryValue(const std::uint8_t value) { m_battery_value_ = value; }

private:
    std::uint8_t m_battery_value_ = 0; //0x0000
    char pad_0001_[3] = {}; //0x0001
    const char* m_id_ = nullptr; //0x0004
    const char* m_version_ = nullptr; //0x0008
    char pad_000_c_[12] = {}; //0x000C
}; //Size: 0x0018
static_assert(sizeof(InsydeFlash) == 0x18);

using CheckPowerStatusFn = bool(__cdecl*)(bool&, InsydeFlash*, bool&);
CheckPowerStatusFn power_status_fn = nullptr;

bool CheckPowerStatus(bool& a1, InsydeFlash* a2, bool& a3)
{
    if (a2->GetBatteryValue() != 100) a2->SetBatteryValue(100);
    return true;
}

using CheckStatusFn = bool(__cdecl*)(void*);
CheckStatusFn check_status_fn = nullptr;

bool CheckStatus(void* a1)
{
    return true;
}

void OnImageLoad()
{
    const auto iscflash = GetModuleHandleA("iscflash.dll");
    if (!iscflash)
    {
        MsgBox("Cannot find iscflash dll!");
        return;
    }

    void* check_power_status = GetProcAddress(iscflash, "?CheckPowerStatus@@YA_NAA_NAAE_N@Z");
    if (!check_power_status)
    {
        MsgBox("Cannot find CheckPowerStatus function!");
        return;
    }

    if (MH_Initialize() != MH_OK)
    {
        MsgBox( "Cannot initialize min hook!");
        return;
    }

    if (MH_CreateHook(check_power_status, &CheckPowerStatus,
                      reinterpret_cast<LPVOID*>(&check_power_status)) != MH_OK)
    {
        MsgBox("Cannot create hook for CheckPowerStatus!");
        return;
    }

    if (MH_EnableHook(MH_ALL_HOOKS) != MH_OK)
    {
        MsgBox("Cannot enable hooks!");
        return;
    }
}

BOOL APIENTRY DllMain(const HMODULE module,
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
