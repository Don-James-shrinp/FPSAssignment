// Origin OvO CopyRight Reserved


#include "AI/Services/BTService_RotateToTarget.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Kismet/KismetMathLibrary.h"

UBTService_RotateToTarget::UBTService_RotateToTarget()
{
	NodeName = TEXT("Rotate To Target Actor");

	INIT_SERVICE_NODE_NOTIFY_FLAGS();

	RotateSpeed = 5.f;
	Interval = 0.f;  //  表示希望该Service在每帧都执行
	RandomDeviation = 0.f;

	InTargetActorKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(ThisClass, InTargetActorKey), AActor::StaticClass());  //  传入的Object必须是AActor的派生类
}

void UBTService_RotateToTarget::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);

	if (UBlackboardData* BlackboardData = GetBlackboardAsset())
	{
		InTargetActorKey.ResolveSelectedKey(*BlackboardData);
	}
}

FString UBTService_RotateToTarget::GetStaticDescription() const
{
	const FString KeyDescription = InTargetActorKey.SelectedKeyName.ToString();

	return FString::Printf(TEXT("Orient rotation to %s Key %s"), *KeyDescription, *GetStaticServiceDescription());
}

void UBTService_RotateToTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UObject* ActorObject = OwnerComp.GetBlackboardComponent()->GetValueAsObject(InTargetActorKey.SelectedKeyName);

	AActor* TargetActor = Cast<AActor>(ActorObject);
	APawn* OwningPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (OwningPawn && TargetActor)
	{
		const FRotator LookAtRotation = 
			UKismetMathLibrary::FindLookAtRotation(
				OwningPawn->GetActorLocation(),
				TargetActor->GetActorLocation()
			);

		const FRotator TargetRotation = FMath::RInterpTo(
			OwningPawn->GetActorRotation(),
			LookAtRotation,
			DeltaSeconds,
			RotateSpeed
			);  //  通过插值在一定时间内转向目标的位置

		OwningPawn->SetActorRotation(TargetRotation);
	}

}
