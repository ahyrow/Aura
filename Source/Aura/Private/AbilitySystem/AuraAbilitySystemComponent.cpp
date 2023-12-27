// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AuraGameplayTags.h"
void UAuraAbilitySystemComponent::AbilityActorInfoSet()
{

	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this,&UAuraAbilitySystemComponent::EffectApplied);

	 //拿到单例
	 const  FAuraGameplayTags& GameplayTags = FAuraGameplayTags::Get();
	// 打印测试访问
	// GameplayTags.Attributes_Secondary_Armor.ToString();
	 GEngine->AddOnScreenDebugMessage(-1,10.f,FColor::Orange,FString::Printf(TEXT("Tag: %s"),
		*GameplayTags.Attributes_Secondary_Armor.ToString()));
}

void UAuraAbilitySystemComponent::EffectApplied
(UAbilitySystemComponent* AbilitySystemComponent,
 const FGameplayEffectSpec& EffectSpec,
 FActiveGameplayEffectHandle ActiveEffectHandle)
{
    FGameplayTagContainer TagContainer;
    EffectSpec.GetAllAssetTags(TagContainer);

	//绑定标签容器
	EffectAssetTags.Broadcast(TagContainer);
	
}
