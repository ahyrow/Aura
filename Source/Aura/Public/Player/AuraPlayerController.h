// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Interaction/EnemyInterface.h"
#include "AuraPlayerController.generated.h"


class IEnemyInterface;
class UInputAction;
class UInputMappingContext;
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
	//»Øµ÷º¯Êý
	void Move(const FInputActionValue& InputActionValue);

	IEnemyInterface* LastActor;
	IEnemyInterface* ThisActor;




};
