// Origin OvO CopyRight Reserved

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameModes/FPSGameModeBase.h"
#include "FPSRaceGameMode.generated.h"

class AFPSEnemyCharacter;
/**
 * 
 */



UENUM(BlueprintType)
enum class ERaceGameState : uint8
{
	BeforeSpawningNewWave,  //  生成下一波前，用于进行一些准备工作
	SpawningWave,	//  生成新一波的敌人
	InBattle,   //  生成完后处于战斗状态
	WaveComplete,  //  当前波次结束
	AllWaveDone,	//  所有波次结束
	PlayerDied
};

USTRUCT(BlueprintType)
struct FEnemyWaveSpawnInfomation
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TSoftClassPtr<AFPSEnemyCharacter> SoftEnemyClassToSpawn;

	UPROPERTY(EditAnywhere)
	int32 MinSpawnCount = 1;  //  每次最少生成的数量

	UPROPERTY(EditAnywhere)
	int32 MaxSpawnCount = 3;  //  每次最多生成数量
};

USTRUCT(BlueprintType)
struct FEnemyWaveSpawnTableRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnyWhere)
	TArray<FEnemyWaveSpawnInfomation> EnemyWaveSpawnDefinitions;

	UPROPERTY(EditAnywhere)
	int32 TotalCountToSpawnInCurrentWave = 1;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameStateChangeDelegate, ERaceGameState, CurrentGameState);
UCLASS()
class FPSGAME_API AFPSRaceGameMode : public AFPSGameModeBase
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:

	void SetCurrentGameState(ERaceGameState NewState);

	void PreloadNextWave();  // 通过异步的方式预加载下一波

	int32 SpawnCurrentWave();  //  生成当前波的敌人，返回生成的敌人数量

	bool IsAllWaveDone();  //  是否生成完所有的波次

	bool ShouldSpawnMoreEnemies();  //  是否需要生成更多的敌人，即查看CurrentWaveSpawnedEnemyCount是否已经大于等于DataTable规定的最大生成数量

	FEnemyWaveSpawnTableRow* GetCurrentWaveSpawnTableRow() const;  //  获取当前波次的Table Row

	UFUNCTION()
	void OnEnemyDestroyed(AActor* DestroyedEnemy);

	
	UPROPERTY()
	ERaceGameState CurrentRaceGameState;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnGameStateChangeDelegate OnGameStateChange;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enemy Wave Definition", meta = (AllowPrivateAccess = "true"))
	UDataTable* EnemyWaveSpawnDataTable;

	UPROPERTY()
	int32 TotalWaveToSpawn;  //  由上面的DataTable决定敌人生成波次数量

	UPROPERTY()
	int32 CurrentWave = 1;  //  当前波次数

	UPROPERTY()
	int32 CurrentAliveEnemyCount = 0;  //  当前波次存活的敌人数量

	UPROPERTY()
	int32 CurrentWaveSpawnedEnemyCount = 0;  // 当前波次生成的敌人数量

	UPROPERTY()
	TArray<AActor*> TargetPoints;  //  用于生成敌人的TargetPoints

	UPROPERTY()
	float TimeElapsedSinceStart = 0.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enemy Wave Definition", meta = (AllowPrivateAccess = "true"))
	float BeforeWaveStartWaitTime = 2.f;  //  生成下一波前的等待时间

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enemy Wave Definition", meta = (AllowPrivateAccess = "true"))
	float SpawnEnemiesDelayTime = 2.f;  //  生成敌人的等待时间

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enemy Wave Definition", meta = (AllowPrivateAccess = "true"))
	float WaveCompleteWaitTime = 5.f;  //  生成一个波次后等待时间

	UPROPERTY()
	TMap<TSoftClassPtr<AFPSEnemyCharacter>, UClass*> PreloadedEnemyClassMap;  //  用于储存预加载的敌人类
};
