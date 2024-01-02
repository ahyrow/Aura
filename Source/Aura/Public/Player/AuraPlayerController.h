// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Interaction/EnemyInterface.h"
#include "AuraPlayerController.generated.h"


struct FGameplayTag;
class UAuraInputConfig;
class UAuraEnhancedInputComponent;
class IEnemyInterface;
class UInputAction;
class UInputMappingContext;
class UAuraAbilitySystemComponent;
struct FInputActionValue;




/**
 * 
 */
UCLASS()
class AURA_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AAuraPlayerController();
protected:
	virtual void BeginPlay() override;
	
	virtual void PlayerTick(float DeltaTime) override;
	  
    virtual void SetupInputComponent() override;


	void CursirTrace();
private:
	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UInputMappingContext> AuraContext;

	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UInputAction> MoveAction;
private:
	//回调函数
	void Move(const FInputActionValue& InputActionValue);
	     
	//TObjectPtr<IEnemyInterface> LastActor;
	IEnemyInterface* LastActor;
	//TObjectPtr<IEnemyInterface> ThisActor;
	IEnemyInterface* ThisActor;


	/* 按键的回调函数 */
	//按下
   void AbilityInputTagPressed(FGameplayTag InputTag);
	//松开
	void AbilityInputTagReleased(FGameplayTag InputTag);
	//按住
	void AbilityInputTagHeld(FGameplayTag InputTag);
	
    UPROPERTY(EditDefaultsOnly,Category="Input")
	TObjectPtr<UAuraInputConfig> InputConfig;

	UPROPERTY()
	TObjectPtr<UAuraAbilitySystemComponent> AuraAbilitySystemComponent;

	UAuraAbilitySystemComponent* GetASC();
};
