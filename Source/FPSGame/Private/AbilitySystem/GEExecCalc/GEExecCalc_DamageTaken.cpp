// Origin OvO CopyRight Reserved


#include "AbilitySystem/GEExecCalc/GEExecCalc_DamageTaken.h"
#include "AbilitySystem/FPSAttributeSet.h"
#include "FPSGameplayTags.h"

#include "FPSDebugHelper.h"
//  定义计算伤害时需要捕获的属性(Attribute)
struct FFPSDamageCapture  
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(DefensePower)
	DECLARE_ATTRIBUTE_CAPTUREDEF(DamageTaken)

	FFPSDamageCapture()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UFPSAttributeSet, DefensePower, Target, false)  //  需要直到目标的防御力，所以是Target而不是Source
		DEFINE_ATTRIBUTE_CAPTUREDEF(UFPSAttributeSet, DamageTaken, Target, false)

	}
};

static const FFPSDamageCapture& GetFPSDamgeCapture()  //  返回局部静态变量的引用，Mayer单例模式
{
	static FFPSDamageCapture FPSDamageCapture;
	return FPSDamageCapture;
}

UGEExecCalc_DamageTaken::UGEExecCalc_DamageTaken()
{

	RelevantAttributesToCapture.Add(GetFPSDamgeCapture().DefensePowerDef);
	RelevantAttributesToCapture.Add(GetFPSDamgeCapture().DamageTakenDef);
}

void UGEExecCalc_DamageTaken::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const FGameplayEffectSpec& EffectSpec = ExecutionParams.GetOwningSpec();

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = EffectSpec.CapturedTargetTags.GetAggregatedTags();
	EvaluateParameters.TargetTags = EffectSpec.CapturedTargetTags.GetAggregatedTags();

	float WeaponBaseDamage = 0.f;  //  武器的基础伤害

	for (const TPair<FGameplayTag, float>& TagMagnitude : EffectSpec.SetByCallerTagMagnitudes)
	{
		if (TagMagnitude.Key.MatchesTagExact(FPSGameplayTags::Shared_SetByCaller_WeaponBaseDamage_Rifle))
		{
			WeaponBaseDamage = TagMagnitude.Value;
		}
	}
	float TargetDefensePower = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(
		GetFPSDamgeCapture().DefensePowerDef,
		EvaluateParameters,
		TargetDefensePower
	);

	checkf(TargetDefensePower > 0.f, TEXT("TargetDefensePower Is Zero!"));
	const float FinalDamageTaken = WeaponBaseDamage / TargetDefensePower;

	if (FinalDamageTaken > 0.f)
	{
		OutExecutionOutput.AddOutputModifier(
			FGameplayModifierEvaluatedData(
				GetFPSDamgeCapture().DamageTakenProperty,
				EGameplayModOp::Override,
				FinalDamageTaken
			)
		);
	}
}
