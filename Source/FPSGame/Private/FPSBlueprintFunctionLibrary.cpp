// Origin OvO CopyRight Reserved


#include "FPSBlueprintFunctionLibrary.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/FPSAbilitySystemComponent.h"

UFPSAbilitySystemComponent* UFPSBlueprintFunctionLibrary::NativeGetFPPASCFromActor(AActor* InActor)
{
    check(InActor);
    return CastChecked<UFPSAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InActor));
}

bool UFPSBlueprintFunctionLibrary::NativeDoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck)
{
    UFPSAbilitySystemComponent* ASC = NativeGetFPPASCFromActor(InActor);

    return ASC->HasMatchingGameplayTag(TagToCheck);
}

void UFPSBlueprintFunctionLibrary::AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag TagToAdd)
{
    UFPSAbilitySystemComponent* ASC = NativeGetFPPASCFromActor(InActor);
    if (!ASC->HasMatchingGameplayTag(TagToAdd))
    {
        ASC->AddLooseGameplayTag(TagToAdd);
    }
}

void UFPSBlueprintFunctionLibrary::RemoveGameplayTagFromActorIfFound(AActor* InActor, FGameplayTag TagToRemove)
{
    UFPSAbilitySystemComponent* ASC = NativeGetFPPASCFromActor(InActor);
    if (ASC->HasMatchingGameplayTag(TagToRemove))
    {
        ASC->RemoveLooseGameplayTag(TagToRemove);
    }
}

void UFPSBlueprintFunctionLibrary::BP_DoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck, EFPSConfirmType& OutConfirmType)
{
    bool HasTag = NativeDoesActorHaveTag(InActor, TagToCheck);
    OutConfirmType = HasTag ? EFPSConfirmType::Yes : EFPSConfirmType::No;
}
