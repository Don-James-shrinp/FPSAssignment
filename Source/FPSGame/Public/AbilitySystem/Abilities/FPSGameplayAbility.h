// Origin OvO CopyRight Reserved

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "FPSTypes/FPSEnumTypes.h"
#include "FPSGameplayAbility.generated.h"


class UFPSAbilitySystemComponent;
class UPawnCombatComponent;
UENUM(BlueprintType)
enum class EFPSAbilityActivationPolicy : uint8  //  Abilty的激活策略
{
	OTriggered,   //  由其他条件触发激活(Input，GameplayEvent)
	OnGiven       //  获得该能力后就立即激活
};
/**
 * 
 */
UCLASS()
class FPSGAME_API UFPSGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

protected:
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	UFUNCTION(BlueprintCallable, Category = "FPS|Ability")
	UFPSAbilitySystemComponent* GetFPSAbilitySystemComponentFromActorInfo() const;  //  从ActorInfo中获取AbilitySystemComponent

	UFUNCTION(BlueprintCallable, Category = "FPS|Ability")
	UPawnCombatComponent* GetPawnCombatComponentFromActorInfo() const;

	FActiveGameplayEffectHandle NativeApplyEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& InSpecHandle);

	UFUNCTION(BlueprintCallable, Category = "FPS|Ability", meta = (DisplayName = "Apply GameplayEffect To Target Actor", ExpandEnumAsExecs = "OutSuccessType"))  //  ExpandEnumAsExecs将枚举类型使用其枚举名称来显式
	FActiveGameplayEffectHandle BP_ApplyEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& InSpecHandle, EFPSSuccessType& OutSuccessType);

	UPROPERTY(EditDefaultsOnly, Category = "FPS|Ability")
	EFPSAbilityActivationPolicy AbilityActivationPolicy = EFPSAbilityActivationPolicy::OTriggered;
public:
	UFUNCTION(BlueprintPure, Category = "FPS|Ability")
	FGameplayEffectSpecHandle MakeDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, float InWeaponDamage);
};
