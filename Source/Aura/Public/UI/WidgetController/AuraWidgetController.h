// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AuraWidgetController.generated.h"



class AAuraPlayerState;
class AAuraPlayerController;
class UAbilitySystemComponent;
class UAuraAttributeSet;
/**
 * 
 */
UCLASS()
class AURA_API UAuraWidgetController : public UObject
{
	GENERATED_BODY()

protected:
	//Íæ¼Ò×´Ì¬
	UPROPERTY(BlueprintReadOnly,Category = "WidgetController")
	TObjectPtr<AAuraPlayerState> PlayerState;

	UPROPERTY(BlueprintReadOnly,Category = "WidgetController")
	TObjectPtr<AAuraPlayerController> PlayerController;

	UPROPERTY(BlueprintReadOnly,Category = "WidgetController")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly,Category = "WidgetController")
	TObjectPtr<UAuraAttributeSet> AttributeSet;

	
};
