// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"



AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	//���AuraContext�Ƿ���Ч
	check(AuraContext);
	
	//������ǿ���������ϵͳ
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);
	Subsystem->AddMappingContext(AuraContext,0);

	//���������ʾ �� ������ʽ
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	//��������ģʽ����
	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);


}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	//
	 
}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
 
}
