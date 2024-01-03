 // Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AuraGameplayTags.h"
#include "AbilitySystem/Abilities/AuraGameplayAbility.h"

void UAuraAbilitySystemComponent::AbilityActorInfoSet()
{

	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this,&UAuraAbilitySystemComponent::ClientEffectApplied);

	 //拿到单例
	 const  FAuraGameplayTags& GameplayTags = FAuraGameplayTags::Get();
	// 打印测试访问
	// GameplayTags.Attributes_Secondary_Armor.ToString();
	 /*GEngine->AddOnScreenDebugMessage(-1,10.f,FColor::Orange,FString::Printf(TEXT("Tag: %s"),
		*GameplayTags.Attributes_Secondary_Armor.ToString()));*/
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

 void UAuraAbilitySystemComponent::AbilityInputTagHeld(const FGameplayTag& InputTag)
 {
	if(!InputTag.IsValid()) return;
    //获得可激活的能力
	for(auto & AbilitySpec : GetActivatableAbilities())
	{
		//检查标签是否匹配
		if(AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			AbilitySpecInputPressed(AbilitySpec);
			//如果没有激活
			if(!AbilitySpec.IsActive())
			{
				//激活
				TryActivateAbility(AbilitySpec.Handle);
				
			}
			
		}
	}
  }

 void UAuraAbilitySystemComponent::AbilityInputTagReleased(const FGameplayTag& InputTag)
 {
	//输入标签是否有效
	if(!InputTag.IsValid()) return;
	//获得可激活的能力
	for(auto & AbilitySpec : GetActivatableAbilities())
	{
		//检查标签是否匹配
		if(AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			//能力spec输入已按下 输入被释放
			AbilitySpecInputReleased(AbilitySpec);
		}
	}
 }

 void UAuraAbilitySystemComponent::ClientEffectApplied_Implementation
(UAbilitySystemComponent* AbilitySystemComponent,
 const FGameplayEffectSpec& EffectSpec,
 FActiveGameplayEffectHandle ActiveEffectHandle)
{
    FGameplayTagContainer TagContainer;
    EffectSpec.GetAllAssetTags(TagContainer);

	//绑定标签容器
	EffectAssetTags.Broadcast(TagContainer);
	
}
