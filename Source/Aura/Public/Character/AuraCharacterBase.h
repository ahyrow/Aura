 // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Interaction/CombatInterface.h"
#include "AuraCharacterBase.generated.h"


class UAbilitySystemComponent;
class UAttributeSet;
class UAuraAttributeSet;
class UGameplayEffect;


UCLASS(Abstract)
class AURA_API AAuraCharacterBase : public ACharacter ,public IAbilitySystemInterface,public ICombatInterface
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
	//����һ��GameplayEffect��  Ĭ����Ҫ����
	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category="Attributes")
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttributes;

	//Ĭ�ϴ�Ҫ����
	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category="Attributes")
	TSubclassOf<UGameplayEffect> DefaultSecondaryAttributes;

	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category="Attributes")
	TSubclassOf<UGameplayEffect> DefaultVitalAttributes;
	 /*
	 //��ʼ����Ҫ����
	void  InitializePrimaryAttributes() const;

	 //��ʼ����Ҫ����
	void  InitializeSecondaryAttributes() const;
	*/
	

	void InitializeDefaultAttributes() const;

	//��ʼ���������Է�װ�ɺ���
	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectclass , float Level) const;

};
