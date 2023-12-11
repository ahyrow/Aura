// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/AuraPlayerState.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystemComponent.h"

AAuraPlayerState::AAuraPlayerState()
{
   

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent -> SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	//AttributeSet=CreateDefaultSubobject<UAttributeSet>("AttributeSet");
    AttributeSet=CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");
	 //������ͬ��  �������Ƶ��
	NetUpdateFrequency = 100.f;
}



UAbilitySystemComponent* AAuraPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}