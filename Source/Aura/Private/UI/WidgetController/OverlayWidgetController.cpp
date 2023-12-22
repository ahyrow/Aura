// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/OverlayWidgetController.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "GameplayEffectTypes.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"

void UOverlayWidgetController::BroadcastInitiaValues()
{   
	//��ȡAura���Լ� �Լ�����ֵ �������ֵ
	UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);
	OnHealthChanged.Broadcast(AuraAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(AuraAttributeSet->GetMaxHealth());

	OnManaChanged.Broadcast(AuraAttributeSet->GetMana());
	OnMaxManaChanged.Broadcast(AuraAttributeSet->GetMaxMana());
}

void UOverlayWidgetController::BindCallbacksToDependcies()
{

	UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetHealthAttribute()).AddLambda(
		[this](const  FOnAttributeChangeData& Data)
		{
			OnHealthChanged.Broadcast(Data.NewValue);
		}
		);
 
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
	{
			OnMaxHealthChanged.Broadcast(Data.NewValue);
	});
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetManaAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnManaChanged.Broadcast(Data.NewValue);
			
		});
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxManaAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnMaxManaChanged.Broadcast(Data.NewValue);
		});
	
    UAuraAbilitySystemComponent* AuraASC=Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent);
	AuraASC->EffectAssetTags.AddLambda(
     [this](const FGameplayTagContainer& AssetTags )
     {
     	
	for(FGameplayTag Tag : AssetTags )
	{
        //��ǩ����
		FGameplayTag MessageTag =FGameplayTag::RequestGameplayTag(FName("Message"));
 
	   if(Tag.MatchesTag(MessageTag))
	   {
            
	   	  const FUIWidgetRow* Row = GetDataTableRowByTag<FUIWidgetRow>(MessageDataTable,Tag);
 
	   	  if(Row!=nullptr) MessageWidgetRowSignature.Broadcast(*Row);
	   	
	   }
	}
	
     });
}	


