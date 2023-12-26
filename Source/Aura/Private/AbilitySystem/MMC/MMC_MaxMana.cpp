// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/MMC/MMC_MaxMana.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Interaction/CombatInterface.h"
class ICombatInterface;

UMMC_MaxMana::UMMC_MaxMana()
{
	//指定要捕获的属性
	IntDef.AttributeToCapture = UAuraAttributeSet::GetIntelligenceAttribute();
	//定义属性源
	IntDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	IntDef.bSnapshot = false;

	//捕获后把IntDef加入MMC捕获定义的数组中
	RelevantAttributesToCapture.Add(IntDef);
	
}

float UMMC_MaxMana::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{

	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const  FGameplayTagContainer* TargetTags=Spec.CapturedTargetTags.GetAggregatedTags();
	//捕获属性并拿到属性值必须先创建FAggregatorEvaluateParameters
	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

   
	float Int = 0.f;
	GetCapturedAttributeMagnitude(IntDef,Spec,EvaluationParameters,Int);
	Int=FMath::Max<float>(Int,0.f);

	//获取到了玩家等级
	ICombatInterface* CombatInterface=Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
	const int32 PlayerLevel = CombatInterface->GetPlayerLevel();

	//基于等级设置属性值 
	return 50.f+2.5f*Int+15.f*PlayerLevel;
	//50+2.5* Int +15*1 =?
	
	
}
