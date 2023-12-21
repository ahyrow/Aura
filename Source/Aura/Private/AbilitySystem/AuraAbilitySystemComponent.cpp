// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AuraAbilitySystemComponent.h"

void UAuraAbilitySystemComponent::AbilityActorInfoSet()
{

	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this,&UAuraAbilitySystemComponent::EffectApplied);
	
}

void UAuraAbilitySystemComponent::EffectApplied
(UAbilitySystemComponent* AbilitySystemComponent,
 const FGameplayEffectSpec& EffectSpec,
 FActiveGameplayEffectHandle ActiveEffectHandle)
{
    FGameplayTagContainer TagContainer;
    EffectSpec.GetAllAssetTags(TagContainer);

	//�󶨱�ǩ����
	EffectAssetTags.Broadcast(TagContainer);
	
}
