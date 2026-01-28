// Origin OvO CopyRight Reserved


#include "PlayerState/FPSPlayerState.h"
#include "Net/UnrealNetwork.h"
#include "Characters/FPSPlayerCharacter.h"
#include "Components/UI/PlayerUIComponent.h"

void AFPSPlayerState::AddKillCount(int32 Amount)
{
	//  服务器有权限修改，客户端仅同步服务器的信息
	if (HasAuthority())
	{
		KillCount += Amount;
	}
}

void AFPSPlayerState::OnRep_KillCount(int32 OldKillCount)
{
	//  TODO: 更新客户端UI，在屏幕右上角展示杀敌数
	AFPSPlayerCharacter* Player = Cast<AFPSPlayerCharacter>(GetPlayerController()->GetPawn());
	Player->GetPlayerUIComponent()->OnKillCountChanged.Broadcast(KillCount);
}

void AFPSPlayerState::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	DOREPLIFETIME(AFPSPlayerState, KillCount);
}
