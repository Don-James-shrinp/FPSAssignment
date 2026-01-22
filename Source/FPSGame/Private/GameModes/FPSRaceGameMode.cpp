// Origin OvO CopyRight Reserved


#include "GameModes/FPSRaceGameMode.h"
#include "Engine/AssetManager.h"
#include "Characters/FPSEnemyCharacter.h"
#include "Engine/TargetPoint.h"
#include "Kismet/GameplayStatics.h"

void AFPSRaceGameMode::BeginPlay()
{
	checkf(EnemyWaveSpawnDataTable, TEXT("Forgot to assign enemy spawn data table!"));

	SetCurrentGameState(ERaceGameState::BeforeSpawningNewWave);

	TotalWaveToSpawn = EnemyWaveSpawnDataTable->GetRowNames().Num();

	PreloadNextWave();
}

void AFPSRaceGameMode::Tick(float DeltaTime)
{
	if (CurrentRaceGameState == ERaceGameState::BeforeSpawningNewWave)
	{
		TimeElapsedSinceStart += DeltaTime;
		if (TimeElapsedSinceStart >= BeforeWaveStartWaitTime)
		{
			TimeElapsedSinceStart = 0.f;
			SetCurrentGameState(ERaceGameState::SpawningWave);
		}
	}

	if (CurrentRaceGameState == ERaceGameState::SpawningWave)
	{
		TimeElapsedSinceStart += DeltaTime;
		
		if (TimeElapsedSinceStart >= SpawnEnemiesDelayTime)
		{
			CurrentWaveSpawnedEnemyCount += SpawnCurrentWave();
			TimeElapsedSinceStart = 0.f;
			SetCurrentGameState(ERaceGameState::InBattle);
		}
	}

	if (CurrentRaceGameState == ERaceGameState::WaveComplete)
	{
		TimeElapsedSinceStart += DeltaTime;
		if (TimeElapsedSinceStart >= WaveCompleteWaitTime)
		{
			TimeElapsedSinceStart = 0.f;
			if (IsAllWaveDone())
			{
				SetCurrentGameState(ERaceGameState::AllWaveDone);
			}
			else
			{
				SetCurrentGameState(ERaceGameState::BeforeSpawningNewWave);
				PreloadNextWave();
			}
		}
	}
}

void AFPSRaceGameMode::SetCurrentGameState(ERaceGameState NewState)
{
	CurrentRaceGameState = NewState;
}

void AFPSRaceGameMode::PreloadNextWave()
{
	PreloadedEnemyClassMap.Empty();

	for (const FEnemyWaveSpawnInfomation& SpawnInfo : GetCurrentWaveSpawnTableRow()->EnemyWaveSpawnDefinitions)
	{
		if (!SpawnInfo.SoftEnemyClassToSpawn.IsNull())
		{
			UAssetManager::GetStreamableManager().RequestAsyncLoad(
				SpawnInfo.SoftEnemyClassToSpawn.ToSoftObjectPath(),
				FStreamableDelegate::CreateLambda(
					[SpawnInfo, this]()
					{
						if (UClass* LoadedEnemyClass = SpawnInfo.SoftEnemyClassToSpawn.Get())
						{
							PreloadedEnemyClassMap.Emplace(SpawnInfo.SoftEnemyClassToSpawn, LoadedEnemyClass);
						}
					}
				)
			);
		}

	}
}

int32 AFPSRaceGameMode::SpawnCurrentWave()
{
	if (TargetPoints.IsEmpty())
	{
		UGameplayStatics::GetAllActorsOfClass(this, ATargetPoint::StaticClass(), TargetPoints);
	}

	checkf(!TargetPoints.IsEmpty(), TEXT("Forgot to place Target Point in Level"));

	int32 EnemiesSpawnedCountThisTime = 0;

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	const FVector SpawnUpOffset(0.f, 0.f, 150.f);

	for (const FEnemyWaveSpawnInfomation& SpawnInfo : GetCurrentWaveSpawnTableRow()->EnemyWaveSpawnDefinitions)
	{
		if (!SpawnInfo.SoftEnemyClassToSpawn.IsNull())
		{
			const int32 RandomSpawnNum = FMath::RandRange(SpawnInfo.MinSpawnCount, SpawnInfo.MaxSpawnCount);
			UClass* LoadedEnemyClass = PreloadedEnemyClassMap.FindChecked(SpawnInfo.SoftEnemyClassToSpawn);

			for (int32 i = 0; i < RandomSpawnNum; i++)
			{
				const int32 RandomTargetPointIndex = FMath::RandRange(0, TargetPoints.Num() - 1);
				const FVector SpawnOrigin = TargetPoints[RandomTargetPointIndex]->GetActorLocation() + SpawnUpOffset;
				const FRotator SpawnRotation = TargetPoints[RandomTargetPointIndex]->GetActorForwardVector().ToOrientationRotator();

				AFPSEnemyCharacter* SpawnedEnemy = GetWorld()->SpawnActor<AFPSEnemyCharacter>(
					LoadedEnemyClass,
					SpawnOrigin,
					SpawnRotation,
					SpawnParameters
				);

				if (SpawnedEnemy)
				{
					SpawnedEnemy->OnDestroyed.AddUniqueDynamic(this, &ThisClass::OnEnemyDestroyed);
					EnemiesSpawnedCountThisTime++;
					CurrentWaveSpawnedEnemyCount++;
				}
				
				if (!ShouldSpawnMoreEnemies())
				{
					return EnemiesSpawnedCountThisTime;
				}
			}
		}

	}

	return EnemiesSpawnedCountThisTime;
}

bool AFPSRaceGameMode::IsAllWaveDone()
{
	return CurrentWave > TotalWaveToSpawn;
}

bool AFPSRaceGameMode::ShouldSpawnMoreEnemies()
{
	return CurrentWaveSpawnedEnemyCount < GetCurrentWaveSpawnTableRow()->TotalCountToSpawnInCurrentWave;
}

FEnemyWaveSpawnTableRow* AFPSRaceGameMode::GetCurrentWaveSpawnTableRow() const
{
	const FName RowName = FName(TEXT("Wave") + FString::FromInt(CurrentWave));  //  波次以Wave+WaveNum的形式命名

	FEnemyWaveSpawnTableRow* CurrentRow = EnemyWaveSpawnDataTable->FindRow<FEnemyWaveSpawnTableRow>(RowName, FString());

	check(CurrentRow);

	return CurrentRow;
}

void AFPSRaceGameMode::OnEnemyDestroyed(AActor* DestroyedEnemy)
{
	CurrentAliveEnemyCount--;
	if (ShouldSpawnMoreEnemies())
	{
		CurrentAliveEnemyCount += SpawnCurrentWave();
	}
	else if (CurrentAliveEnemyCount == 0)
	{
		CurrentWaveSpawnedEnemyCount = 0;
		SetCurrentGameState(ERaceGameState::WaveComplete);
	}
}
