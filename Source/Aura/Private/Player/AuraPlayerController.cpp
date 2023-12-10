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
	//检查AuraContext是否有效
	check(AuraContext);

	//设置增强玩家输入子系统
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);
	Subsystem->AddMappingContext(AuraContext, 0);

	//设置鼠标显示 及 常规样式
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	//设置输入模式（）
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
* 鼠标捕捉会有以下几种情况
* A.上一个(LastActor)对象和当前(thisActor)对象为空
*   Do nothing
* 
* B.上一个(LastActor)对象为空，当前(ThisActor)对象有效
*   ThisActor Highlight
* C.上一个(LastActor)对象有效，当前(ThisActor)对象为空
*   UnHightlight LastActor
* D.上一个(LastActor)对象和当前(ThisActor)对象都有效
*    LastActor UnHightlight / ThisActor Hightlight
* 
* E.上一个(LastActor)对象和当前(ThisActor)对象相等,并且是同一个对象
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
