// Origin OvO CopyRight Reserved


#include "FPSBlueprintFunctionLibrary.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/FPSAbilitySystemComponent.h"
#include "GenericTeamAgentInterface.h"

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

bool UFPSBlueprintFunctionLibrary::IsTargetPawnHostile(APawn* QueryPawn, APawn* TargetPawn)
{
    check(QueryPawn && TargetPawn);
    IGenericTeamAgentInterface* QueryTeamAgent = Cast<IGenericTeamAgentInterface>(QueryPawn->GetController());
    IGenericTeamAgentInterface* TargetTeamAgent = Cast<IGenericTeamAgentInterface>(TargetPawn->GetController());
    if (QueryTeamAgent && TargetTeamAgent)
    {
        return QueryTeamAgent->GetGenericTeamId() != TargetTeamAgent->GetGenericTeamId();
    }

    return false;
}
