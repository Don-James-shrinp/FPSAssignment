// Origin OvO CopyRight Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSWeaponBase.generated.h"

class UStaticMeshComponent;

UCLASS()
class FPSGAME_API AFPSWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AFPSWeaponBase();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapons")
	TObjectPtr<UStaticMeshComponent> WeaponStaticMesh;


};
