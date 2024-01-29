// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AuraAbilitySystemLibrary.h"

#include "Game/AuraGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Player/AuraPlayerState.h"
#include "UI/HUD/AuraHUD.h"
#include "UI/WidgetController/AuraWidgetController.h"

UOverlayWidgetController* UAuraAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{

	if(APlayerController* PC= UGameplayStatics::GetPlayerController(WorldContextObject,0))
	{
     if(AAuraHUD* AuraHUD = Cast<AAuraHUD>(PC->GetHUD()))
     {
        AAuraPlayerState* PS=PC->GetPlayerState<AAuraPlayerState>();
     	UAbilitySystemComponent* ABS=PS->GetAbilitySystemComponent();
     	UAttributeSet* AS =PS->GetAttributeSet();
        const FWidgetControllerParms WidgetControllerParms(PC,PS,ABS,AS);
     	return AuraHUD->GetOverlayWidgetController(WidgetControllerParms);
     	
     }
		
	}
	return nullptr;

}

UAttributeMenuWidgetController* UAuraAbilitySystemLibrary::GetAttributeMenuWidgetController(
	const UObject* WorldContextObject)
{

	if(APlayerController* PC= UGameplayStatics::GetPlayerController(WorldContextObject,0))
	{
		if(AAuraHUD* AuraHUD = Cast<AAuraHUD>(PC->GetHUD()))
		{
			AAuraPlayerState* PS=PC->GetPlayerState<AAuraPlayerState>();
			UAbilitySystemComponent* ABS=PS->GetAbilitySystemComponent();
			UAttributeSet* AS =PS->GetAttributeSet();
			const FWidgetControllerParms WidgetControllerParms(PC,PS,ABS,AS);
     	
			return AuraHUD->GetAttributeMenuWidgetController(WidgetControllerParms);
     	
		}
		
	}


	return nullptr;
}

void UAuraAbilitySystemLibrary::InitializeDefaultAttributes(const UObject* WorldContextObject,ECharacterClass CharacterClass, float Level,UAbilitySystemComponent* ASC)
{
     //获取游戏模式
	AAuraGameModeBase* AuraGameModeBase= Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	if(!AuraGameModeBase) return;


	AActor* AvatarActor = ASC->GetAvatarActor(); 
	//拿到枚举对应的信息
	UCharacterClassInfo* CharacterClassInfo = AuraGameModeBase->CharacterClassInfo;
	FCharacterClassDefaultInfo ClassDefaultInfo =CharacterClassInfo->GetClassDefaultInfo(CharacterClass);
	//应用GE
    FGameplayEffectContextHandle PrimaryAttributesContextHandle = ASC->MakeEffectContext();
	PrimaryAttributesContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle PrimaryAttributesSpecHandle = ASC->MakeOutgoingSpec(ClassDefaultInfo.PrimaryAttributes,Level,PrimaryAttributesContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf( *PrimaryAttributesSpecHandle.Data.Get());

	FGameplayEffectContextHandle SecondaryAttributesContextHandle = ASC->MakeEffectContext();
	SecondaryAttributesContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle SecondaryAttributesSpecHandle = ASC->MakeOutgoingSpec(CharacterClassInfo->SecondaryAttributes,Level,SecondaryAttributesContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf( *SecondaryAttributesSpecHandle.Data.Get());

	FGameplayEffectContextHandle  VitalAttributesContextHandle = ASC->MakeEffectContext();
	VitalAttributesContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle VitalAttributesSpecHandle = ASC->MakeOutgoingSpec(CharacterClassInfo->VitalAttributes,Level,VitalAttributesContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf( *VitalAttributesSpecHandle.Data.Get());
}

void UAuraAbilitySystemLibrary::GiveStartupAbilities(const UObject* WorldContextObject, UAbilitySystemComponent* ASC)
{
	//获取游戏模式
	AAuraGameModeBase* AuraGameModeBase= Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	if(!AuraGameModeBase) return;
	UCharacterClassInfo* CharacterClassInfo = AuraGameModeBase->CharacterClassInfo;

	for(auto AbilityClass : CharacterClassInfo->CommonAbilities)
	{
		//建立规范
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass,1);
		ASC->GiveAbility(AbilitySpec);
     	
	}

}
