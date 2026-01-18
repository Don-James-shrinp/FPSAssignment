// Origin OvO CopyRight Reserved


#include "Controllers/FPSPlayerController.h"

FGenericTeamId AFPSPlayerController::GetGenericTeamId() const
{
    return FGenericTeamId(0);  //  设置Player的TeamID为0，使其小于Enemy的Team ID，能够被识别为敌对
}
