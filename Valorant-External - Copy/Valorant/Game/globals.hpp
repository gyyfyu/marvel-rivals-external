#pragma once
#include <Windows.h>

HWND Entryhwnd = NULL;
int processid = 0;

namespace offsets
{
    DWORD
        Gameinstance = 0x0270,

        Ulevel = 0x38,

        LocalPlayers = 0x40,

        PlayerController = 0x38,

        PlayerCameraManager = 0x0540,

        MyHUD = 0x538,

        AcknowledgedPawn = 0x0530,

        PlayerState = 0x04A8,

        TeamComponent = 0x628, //NO

        TeamID = 0x05A0,

        UniqueID = 0x04A8,//NO
        FNameID = 0x18,//NO
        AActorArray = 0xa8,

        playerarray = 0x0488,

        RootComponent = 0x02B8,

        RelativeLocation = 0x0188,

        ComponentToWorld = 0x2E0,//NO

        bIsDormant = 0x05B0,
        Health = 0x12F4,
        BoneArray = 0x610,
        BoneArrayCache = BoneArray + 0x10,
        BoneCount = 0x610 + 0x08,

        MeshComponent = 0x0470,
        DamageHandler = 0x9a8;

}

namespace Settings
{
    inline bool bMenu = true;

    namespace Visuals
    {
        inline bool bSnaplines = true;
        inline bool bDistance = false;
        inline bool bBox = true;
        inline bool bBoxOutlined = false;
        inline bool bHealth = false;

        inline float BoxWidth = 1.0f;
    }
}