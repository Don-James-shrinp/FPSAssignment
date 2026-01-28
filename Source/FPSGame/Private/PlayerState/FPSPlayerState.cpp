// Origin OvO CopyRight Reserved


#include "PlayerState/FPSPlayerState.h"
#include "Net/UnrealNetwork.h"

void AFPSPlayerState::OnRep_KillCount(int32 OldKillCount)
{
	//  TODO: 更新客户端UI，在屏幕右上角展示杀敌数
}

void AFPSPlayerState::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	DOREPLIFETIME(AFPSPlayerState, KillCount);
}
