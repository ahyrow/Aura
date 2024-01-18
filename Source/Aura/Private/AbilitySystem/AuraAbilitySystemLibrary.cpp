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

void UAuraAbilitySystemLibrary::InitializeDefaultAttributes(const UObject* WorldContextObject,ECharacterClass CharacterClass, float Level)
{
     //获取游戏模式
	AAuraGameModeBase* AuraGameModeBase= Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	if(!AuraGameModeBase) return;
	//拿到枚举对应的信息
	FCharacterClassDefaultInfo ClassDefaultInfo =AuraGameModeBase->CharacterClassInfo->GetClassDefaultInfo(CharacterClass);
}
