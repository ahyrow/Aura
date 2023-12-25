// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "AuraCharacterBase.generated.h"


class UAbilitySystemComponent;
class UAttributeSet;
class UAuraAttributeSet;
class UGameplayEffect;


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

protected:
	//创建一个GameplayEffect类  默认主要属性
	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category="Attributes")
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttributes;

	//默认次要属性
	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category="Attributes")
	TSubclassOf<UGameplayEffect> DefaultSecondaryAttributes;

	 /*
	 //初始化主要属性
	void  InitializePrimaryAttributes() const;

	 //初始化次要属性
	void  InitializeSecondaryAttributes() const;
	*/
	

	void InitializeDefaultAttributes() const;

	//初始化所有属性封装成函数
	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectclass , float Level) const;

};
