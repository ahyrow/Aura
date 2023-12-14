// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "OverlayWidgetController.generated.h"

/**
 * 
 */

//声明多播代理
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature ,float, NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChangedSignature, float, NewMaxHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnManaChangedSignature, float, NewMana);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxManaChangedSignature, float, NewMaxMana);


UCLASS(BlueprintType,Blueprintable)
class AURA_API UOverlayWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()


public:

	virtual void BroadcastInitiaValues() override;

	virtual void  BindCallbacksToDependcies() override;
public:
	//创建代理
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes") //蓝图可分配
	FOnHealthChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes") //蓝图可分配
	FOnMaxHealthChangedSignature OnMaxHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes") //蓝图可分配
	FOnManaChangedSignature OnManaChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes") //蓝图可分配
	FOnMaxManaChangedSignature OnMaxManaChanged;

protected:
	void HealthChanged(const  FOnAttributeChangeData& Data) const;

	void MaxHealthChanged(const  FOnAttributeChangeData& Data) const;

	void ManaChanged(const  FOnAttributeChangeData& Data) const;

	void MaxManaChanged(const  FOnAttributeChangeData& Data) const;
};
