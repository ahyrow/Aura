// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "AuraPlayerState.generated.h"

class UAbilitySystemComponent;
class UAttributeSet; 
class UAuraAttributeSet;


/**
 * 
 */
UCLASS()
class AURA_API AAuraPlayerState : public APlayerState , public IAbilitySystemInterface
{
	GENERATED_BODY()

public:

	AAuraPlayerState();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override ;

	UAttributeSet* GetAttributeSet() { return AttributeSet; };

public:
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
	/*UPROPERTY()
	TObjectPtr<UAuraAttributeSet> AttributeSet;*/

};