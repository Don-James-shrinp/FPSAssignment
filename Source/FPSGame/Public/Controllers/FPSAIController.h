// Origin OvO CopyRight Reserved

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "FPSAIController.generated.h"

class UAIPerceptionComponent;
class UAISenseConfig_Sight;
/**
 * 
 */
UCLASS()
class FPSGAME_API AFPSAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AFPSAIController(const FObjectInitializer& ObjectInitializer);

	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;  // 获取当前Controller对其他Actor的态度是敌对还是友好

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UAIPerceptionComponent* EnemyPerceptionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UAISenseConfig_Sight* AISenseConfig_Sight;

	UFUNCTION()
	void OnEnemyPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);  //  当Perception更新时的回调函数

private:
	UPROPERTY(EditDefaultsOnly, Category = "Detour Crowd Avoidance Config")
	bool bEnableDetourCrowdAvoidance = true;  //  用于避免Enemy AI之间的碰撞

	UPROPERTY(EditDefaultsOnly, Category = "Detour Crowd Avoidance Config", meta = (EditCondition = "bEnableDetourCrowdAvoidance", UIMin = "1", UIMax = "4"))
	int32 DetourCrowdAvoidanceQuality = 4;

	UPROPERTY(EditDefaultsOnly, Category = "Detour Crowd Avoidance Config", meta = (EditCondition = "bEnableDetourCrowdAvoidance"))
	float CollisionQueryRange = 600.f;

	UPROPERTY(EditDefaultsOnly, Category = "Perception Config")
	FName TargetObjectKeyName = "TargetActor";

};
