// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AuraWidgetController.generated.h"



class APlayerState;
class APlayerController;
class UAbilitySystemComponent;
class UAttributeSet;

/**
 * 
 */
USTRUCT(BlueprintType)
struct FWidgetControllerParms
{

	GENERATED_BODY()
	
	FWidgetControllerParms(){}
	FWidgetControllerParms(APlayerController* PC, APlayerState* PS,UAbilitySystemComponent* ASC, UAttributeSet* AS):
	PlayerController(PC),PlayerState(PS),AbilitySystemComponent(ASC),AttributeSet(AS){}
    UPROPERTY(EditAnywhere,BlueprintReadWrite)
	APlayerController* PlayerController = nullptr;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	APlayerState* PlayerState = nullptr;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UAbilitySystemComponent* AbilitySystemComponent = nullptr;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UAttributeSet* AttributeSet = nullptr;
};
UCLASS()
class AURA_API UAuraWidgetController : public UObject
{
	GENERATED_BODY()

public:
	//创建初始化结构体函数
	UFUNCTION(BlueprintCallable)
	void SetWidgetControllerParms(const FWidgetControllerParms& WCParms);

	virtual void BroadcastInitiaValues();

	//绑定依赖项的回调函数
	virtual void BindCallbacksToDependcies();
protected:
	//玩家状态
	UPROPERTY(BlueprintReadOnly,Category = "WidgetController")
	TObjectPtr<APlayerState> PlayerState; 

	UPROPERTY(BlueprintReadOnly,Category = "WidgetController")
	TObjectPtr<APlayerController> PlayerController;

	UPROPERTY(BlueprintReadOnly,Category = "WidgetController")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly,Category = "WidgetController")
	TObjectPtr<UAttributeSet> AttributeSet;

	
};
