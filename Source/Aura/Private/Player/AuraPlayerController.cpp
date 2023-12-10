// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"



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
	Subsystem->AddMappingContext(AuraContext, 0);

	//���������ʾ �� ������ʽ
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	//��������ģʽ����
	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}
void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	
	CursirTrace();
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
   
	const FVector2D IntputAxisVector = InputActionValue.Get<FVector2D>();

	const FRotator Rotation = GetControlRotation();
	
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector ForwarDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if(APawn* ControllerPawn=GetPawn<APawn>())
	{
		ControllerPawn->AddMovementInput(ForwarDirection, IntputAxisVector.Y);

		ControllerPawn->AddMovementInput(RightDirection, IntputAxisVector.X);
 	}
		
}

void AAuraPlayerController::CursirTrace()
{
	FHitResult CursirHit;

	GetHitResultUnderCursor(ECC_Visibility, false, CursirHit);

	
	if (!CursirHit.bBlockingHit)
		return;

	LastActor = ThisActor;
 	ThisActor=Cast<IEnemyInterface>(CursirHit.GetActor());
/*
* ��겶׽�������¼������
* A.��һ��(LastActor)����͵�ǰ(thisActor)����Ϊ��
*   Do nothing
* 
* B.��һ��(LastActor)����Ϊ�գ���ǰ(ThisActor)������Ч
*   ThisActor Highlight
* C.��һ��(LastActor)������Ч����ǰ(ThisActor)����Ϊ��
*   UnHightlight LastActor
* D.��һ��(LastActor)����͵�ǰ(ThisActor)������Ч
*    LastActor UnHightlight / ThisActor Hightlight
* 
* E.��һ��(LastActor)����͵�ǰ(ThisActor)�������,������ͬһ������
*   Do nothing 
*/
	if(LastActor==nullptr)
	{
	  if(ThisActor!=nullptr)
	  {   
		  //case :B
		  ThisActor->HightlightActor();
		 
	  }
	  else
	  {
          //case :A
		  //Do Nothing
	  }
	
	}
	else
	{
		if(ThisActor==nullptr)
		{
		   //case :C
			LastActor->UnHightlightActor();
		
		}
		else
		{

			
            if(LastActor!=ThisActor)
			{   //case :D
				LastActor->UnHightlightActor();
				ThisActor->HightlightActor();
			}
			else
			{   //case :E
				//Do Nothing
			}
			
		}
	}


}
