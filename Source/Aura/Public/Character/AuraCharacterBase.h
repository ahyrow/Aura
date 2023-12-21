// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "AuraCharacterBase.generated.h"


class UAbilitySystemComponent;
class UAttributeSet;
class UAuraAttributeSet;


UCLASS(Abstract)
class AURA_API AAuraCharacterBase : public ACharacter ,public IAbilitySystemInterface
{
	GENERATED_BODY()

public:	
	AAuraCharacterBase();
	
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override ;
	UAttributeSet* GetAttributeSet() { return AttributeSet; };
	//UAuraAttributeSet* GetAttributeSet() { return AttributeSet; };

protected:
	virtual void BeginPlay() override;

	virtual void InitAbilityActorInfo();
	

public:
	UPROPERTY(EditAnywhere)
	TObjectPtr<USkeletalMeshComponent> Weapon;

    UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
    UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
	//UPROPERTY()
	//TObjectPtr<UAuraAttributeSet> AttributeSet;

};
