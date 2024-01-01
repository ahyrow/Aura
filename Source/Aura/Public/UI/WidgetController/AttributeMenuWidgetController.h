// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "AttributeMenuWidgetController.generated.h"


class UAttributeInfo;
struct FAuraAttributeInfo;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttributeInfoSignature, const FAuraAttributeInfo&,Info);

/**
 * 
 */
UCLASS(BlueprintType,Blueprintable)
class AURA_API UAttributeMenuWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()
public:

	virtual void BindCallbacksToDependcies() override;
	
	virtual void BroadcastInitiaValues() override;

	//创建代理 并且在蓝图可分配
	UPROPERTY(BlueprintAssignable,Category="GAS|Attributes")
	FAttributeInfoSignature AttributeInfoDelegate;


protected:

	//声明属性信息数据资产的指针
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UAttributeInfo> AttributeInfo;
};
