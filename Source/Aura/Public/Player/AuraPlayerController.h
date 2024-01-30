// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Interaction/EnemyInterface.h"
#include "AuraPlayerController.generated.h"


class UDamageTextComponent;
class USplineComponent;
class UAuraInputConfig;
class IEnemyInterface;
class UInputAction;
class UInputMappingContext;
class UAuraAbilitySystemComponent;
struct FGameplayTag;
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
	virtual void PlayerTick(float DeltaTime) override;

	UFUNCTION(Client,Reliable)
	void ShowDamageNumber(float DamageAmount , ACharacter* TargetCharacter);
protected:
	virtual void BeginPlay() override;
    virtual void SetupInputComponent() override;

    /* 鼠标检测 */
	void CursirTrace();
	FHitResult CursirHit;
private:
	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UInputMappingContext> AuraContext;

	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UInputAction> ShiftAction;

	UPROPERTY(EditDefaultsOnly,Category="Input")
	TObjectPtr<UAuraInputConfig> InputConfig;


	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDamageTextComponent> DamageTextComponentClass;
private:
	
	//移动回调函数
	void Move(const FInputActionValue& InputActionValue);
	
	/* 按键的回调函数 */
	//按下
   void AbilityInputTagPressed(FGameplayTag InputTag);
	//松开
	void AbilityInputTagReleased(FGameplayTag InputTag);
	//按住
	void AbilityInputTagHeld(FGameplayTag InputTag);

	/*Shift*/
	void ShiftPressed(){bShiftKeyDown = true;};
	void ShiftReleased(){bShiftKeyDown = false; };

	bool bShiftKeyDown = false;

	//自动运行
	void AutoRun();
private:

	
	FVector CacheDestination = FVector::Zero();
	
	float FollowTime = 0.f;
	
	float ShortPressThreshold = 0.5f;
	
	bool bAutoRunning = false;

	bool bTargeting = false;

	//半径浮点数
	UPROPERTY(EditDefaultsOnly)
	float AutoRunAcceptanceRadius= 50.f;
	

    UPROPERTY(VisibleAnywhere)
    TObjectPtr<USplineComponent> Spline;

	
private:

	//拿到AuraASC指针
	UPROPERTY()
	TObjectPtr<UAuraAbilitySystemComponent> AuraAbilitySystemComponent;

	UAuraAbilitySystemComponent* GetASC();



private:
	/*  鼠标捕捉AI亮边   */
	//TObjectPtr<IEnemyInterface> LastActor;
	IEnemyInterface* LastActor;
	//TObjectPtr<IEnemyInterface> ThisActor;
	IEnemyInterface* ThisActor;
	
};
