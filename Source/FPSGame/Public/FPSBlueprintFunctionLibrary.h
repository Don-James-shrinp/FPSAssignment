// Origin OvO CopyRight Reserved

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FPSTypes/FPSEnumTypes.h"
#include "FPSBlueprintFunctionLibrary.generated.h"

class UFPSAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class FPSGAME_API UFPSBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	static UFPSAbilitySystemComponent* NativeGetFPPASCFromActor(AActor* InActor);  //  Native前缀表示纯C++调用

	static bool NativeDoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck);

	UFUNCTION(BlueprintCallable, Category = "FPS|FunctionLibrary")
	static void AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag TagToAdd);

	UFUNCTION(BlueprintCallable, Category = "FPS|FunctionLibrary")
	static void RemoveGameplayTagFromActorIfFound(AActor* InActor, FGameplayTag TagToRemove);

	UFUNCTION(BlueprintCallable, Category = "FPS|FunctionLibrary", meta = (DisplayName = "Does Actor Have Tag", ExpandEnumAsExecs = "OutConfirmType"))
	static void BP_DoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck, EFPSConfirmType& OutConfirmType);

	UFUNCTION(BlueprintPure, Category = "FPS|FunctionLibrary")
	static bool IsTargetPawnHostile(APawn* QueryPawn, APawn* TargetPawn);  // 查询QueryPawn对TargetPawn的attitude，是友好还是敌对


};
