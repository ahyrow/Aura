// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/ExecCalc/ExecCalc_Damage.h"
#include "AbilitySystemComponent.h"

struct AuraDamageStatics
{
	AuraDamageStatics()
	{
		
	}
};

static const AuraDamageStatics& DamageStatics()
{
   static  AuraDamageStatics DStatics;
	return DStatics;
};


UExecCalc_Damage::UExecCalc_Damage()
{
	
}

void UExecCalc_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
     //���Է���ӵ��GE��Դ��Ŀ�������ϵͳ��� ��  ӵ���� �Լ�Spec��
	const UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	const UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();

	const AActor* SourceAvatar  = SourceASC ? SourceASC->GetAvatarActor():nullptr;
	const AActor* TargetAvatar = TargetASC ? TargetASC->GetAvatarActor():nullptr;

	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();
}
