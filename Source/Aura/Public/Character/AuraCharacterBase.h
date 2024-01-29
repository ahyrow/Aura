 // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Interaction/CombatInterface.h"
#include "AuraCharacterBase.generated.h"


class UGameplayAbility;
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

	//重写战斗接口提供的函数
    virtual UAnimMontage* GetHitReactMontage_Implementation()  override;
protected:
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo();
	
	virtual void InitializeDefaultAttributes() const;
public:
	UPROPERTY(EditAnywhere,Category="Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;

	UPROPERTY(EditAnywhere,Category="Combat")
	//武器插槽名称
	FName WeaponTipSocketName;
	//实现战斗接口函数
	virtual FVector GetCombatSocketLocation() override; 



	virtual void Die() override;

	//网络多播
	UFUNCTION(NetMulticast,Reliable)
	virtual void MulticastHandleDeath();
	
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
	

	

	

	//��ʼ���������Է�װ�ɺ���
	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectclass , float Level) const;


	//添加角色能力函数
	void AddCharacterAbilities();


	/*
	 * 溶解效果
	 */
    //替换溶解材质的方法
	void Dissolve();

	//溶解时间
	void StartDissolveTimeLine(UMaterialInstance* DynamicMaterialInstance);
	
	//创建材质实例
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TObjectPtr<UMaterialInstance> DissolveMaterrialInstance;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TObjectPtr<UMaterialInstance> WeaponDissolveMaterrialInstance;
private:
	//游戏开始时赋予的角色能力
	UPROPERTY(EditAnywhere,Category="Abilities")
	TArray<TSubclassOf<UGameplayAbility>>  StartupAbilities;

	UPROPERTY(EditAnywhere,Category="Combat")
	TObjectPtr<UAnimMontage> HitReactMontage;

};
