// Origin OvO CopyRight Reserved

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystem/FPSAbilitySystemComponent.h"
#include "FPSAttributeSet.generated.h"

class IPawnUIInterface;

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)
/**
 * 
 */
UCLASS()
class FPSGAME_API UFPSAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	UFPSAttributeSet();

	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;  //  当GameplayEffect作用与AttributeSet改变Attribute后执行

	UPROPERTY(BlueprintReadOnly, Category = "Health", ReplicatedUsing = OnRep_CurrentHealth)
	FGameplayAttributeData CurrentHealth;
	ATTRIBUTE_ACCESSORS(UFPSAttributeSet, CurrentHealth)

	UPROPERTY(BlueprintReadOnly, Category = "Health", Replicated)
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UFPSAttributeSet, MaxHealth)

	UPROPERTY(BlueprintReadOnly, Category = "Defense", Replicated)
	FGameplayAttributeData DefensePower;  //  防御力
	ATTRIBUTE_ACCESSORS(UFPSAttributeSet, DefensePower)

	UPROPERTY(BlueprintReadOnly, Category = "Damage", Replicated)
	FGameplayAttributeData DamageTaken;  //  收到的伤害
	ATTRIBUTE_ACCESSORS(UFPSAttributeSet, DamageTaken)

	virtual void GetLifetimeReplicatedProps(TArray< class FLifetimeProperty >& OutLifetimeProps) const override;

	UFUNCTION()
	virtual void OnRep_CurrentHealth(const FGameplayAttributeData& OldHealth);
private:
	TWeakInterfacePtr<IPawnUIInterface> CachedPawnUIInterface;
};
