// Origin OvO CopyRight Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FPSPawnExtensionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPSGAME_API UFPSPawnExtensionComponent : public UActorComponent
{
	GENERATED_BODY()
protected:
	template <typename T>
	T* GetOwningPawn() const  //  模板函数，用于获取指定类型的APawn（必须派生自APawn）
	{
		static_assert(TPointerIsConvertibleFromTo<T, APawn>::Value, TEXT("Template Parameter 'T' must derive from APawn"));
		return CastChecked<T>(GetOwner());
	}
		
	APawn* GetOwningPawn() const  // 获取APawn类型的OwningPawn
	{
		return GetOwningPawn<APawn>();
	}

	template <typename T>
	T* GetOwningController() const  //  获取指定类型的APawn的Controller
	{
		static_assert(TPointerIsConvertibleFromTo<T, AController>::Value, TEXT("Template Parameter 'T' must derive from AController"));
		return GetOwningPawn<APawn>()->GetController<T>();
	}
};
