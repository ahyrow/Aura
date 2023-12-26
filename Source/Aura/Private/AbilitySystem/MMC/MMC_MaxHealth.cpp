// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/MMC/MMC_MaxHealth.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Interaction/CombatInterface.h"

UMMC_MaxHealth::UMMC_MaxHealth()
{
    //指定要捕获的属性
	VigorDef.AttributeToCapture = UAuraAttributeSet::GetVigorAttribute();
	//定义属性源
	VigorDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	VigorDef.bSnapshot = false;

	//捕获后把VigorDef加入MMC捕获定义的数组中
	RelevantAttributesToCapture.Add(VigorDef);
}

float UMMC_MaxHealth::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	 //
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
    const  FGameplayTagContainer* TargetTags=Spec.CapturedTargetTags.GetAggregatedTags();
    //捕获属性并拿到属性值必须先创建FAggregatorEvaluateParameters
	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

   
	float Vigor = 0.f;
	GetCapturedAttributeMagnitude(VigorDef,Spec,EvaluationParameters,Vigor);
    Vigor=FMath::Max<float>(Vigor,0.f);

	//获取到了玩家等级
	ICombatInterface* CombatInterface=Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
	const int32 PlayerLevel = CombatInterface->GetPlayerLevel();

	//基于等级设置属性值 
	return 80.f+2.5f*Vigor+10.f*PlayerLevel;
	//80+2.5* vigor +10*1 =?
}
