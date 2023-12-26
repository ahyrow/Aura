// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "AuraPlayerState.generated.h"

class UAuraAbilitySystemComponent;
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

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;


	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override ;
	UAttributeSet* GetAttributeSet() { return AttributeSet; };

	FORCEINLINE int32 GetPlayerLevel() const{return Level;};

public:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
	/*UPROPERTY()
	TObjectPtr<UAuraAttributeSet> AttributeSet;*/

private:
	UPROPERTY(VisibleAnywhere,ReplicatedUsing = OnRep_Level)
	int32 Level = 1;
 //ÍøÂç¸´ÖÆ
	UFUNCTION()
	void OnRep_Level(int32 OldLevel);
};
