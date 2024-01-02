// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AuraGameplayTags.h"
#include "AbilitySystem/Abilities/AuraGameplayAbility.h"

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

void UAuraAbilitySystemComponent::AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StarupAbilities)
{
    
     for(TSubclassOf<UGameplayAbility> AbilityClass :  StarupAbilities)
     {
     	//建立规范
     	FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass,1);
     	if(const UAuraGameplayAbility* AuraAbility = Cast<UAuraGameplayAbility>(AbilitySpec.Ability))
     	{
     		//动态添加标签
     		AbilitySpec.DynamicAbilityTags.AddTag(AuraAbility->StartupInputTag);
     		//给予能力
     		GiveAbility(AbilitySpec);
     	}
     	
     	//给予并激活
     	/*GiveAbilityAndActivateOnce(AbilitySpec);*/
     	
     }
	
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
