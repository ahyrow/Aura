// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/AuraPlayerController.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AuraGameplayTags.h"
#include "EnhancedInputSubsystems.h"
#include "GameplayTagContainer.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Components/SplineComponent.h"
#include "Input/AuraEnhancedInputComponent.h"


AAuraPlayerController::AAuraPlayerController()
{

	bReplicates = true;

	Spline = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));

}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	//检查AuraContext是否有效
	check(AuraContext);

	//设置增强玩家输入子系统
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	//check(Subsystem);
	if(Subsystem)
	{
		Subsystem->AddMappingContext(AuraContext, 0);

	}

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

	AutoRun();
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	/* 修改为自己的增强输入组件 */
	//EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
	UAuraEnhancedInputComponent* AuraEnhancedInputComponent = CastChecked<UAuraEnhancedInputComponent>(EnhancedInputComponent);
	AuraEnhancedInputComponent->BindAction(MoveAction,ETriggerEvent::Triggered,this,&AAuraPlayerController::Move);

	AuraEnhancedInputComponent->BindAbilityActions
	(InputConfig,this,&ThisClass::AbilityInputTagPressed,&ThisClass::AbilityInputTagReleased,&ThisClass::AbilityInputTagHeld);
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

void AAuraPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	
	if(InputTag.MatchesTagExact(FAuraGameplayTags::Get().InputTag_LMB))
	{

		bTargeting = ThisActor? true : false;
		bAutoRunning=false;
		
	}

	//GEngine->AddOnScreenDebugMessage(1,3.f,FColor::Blue,*InputTag.ToString());
	
}

void AAuraPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	//当不是鼠标左键被按住时 可以执行游戏能力
	if(!InputTag.MatchesTagExact(FAuraGameplayTags::Get().InputTag_LMB))
	{
		if(GetASC())
		{
			GetASC()->AbilityInputTagReleased(InputTag);
		}
		return;
	}
	//当thisActor为空指针时执行游戏能力    
	if(bTargeting)
	{
		if(GetASC())
		{
			GetASC()->AbilityInputTagHeld(InputTag);
		}
	}
	else
	{
		APawn* ControllerPawn = GetPawn(); 
		//判断浮动时间是否小于短按时间
         if(FollowTime<=ShortPressThreshold&&ControllerPawn)
         {
	         //先创建自动导航
         if( UNavigationPath* NavigaPath=
         		UNavigationSystemV1::FindPathToLocationSynchronously(this,ControllerPawn->GetActorLocation(),CacheDestination))
         {
         	//每次创建前先清理样条点
         	Spline->ClearSplinePoints();
         	//循环遍历导航的整个路径点
         	for(auto& PointLoc : NavigaPath->PathPoints)
         	{
         		//路径点加入 样条线
         		Spline->AddSplinePoint(PointLoc,ESplineCoordinateSpace::World);
         	}
         	//如果点击碰到有障碍物阻挡的情况下 重置一下目的地 将目的地设置为样条线的最后一个点(因为是可到达的点) 
         	CacheDestination = NavigaPath->PathPoints[NavigaPath->PathPoints.Num()-1];
         	//是否自动running 变为true
            bAutoRunning = true;
         }
         }
		FollowTime = 0.f;
		bTargeting = false;
	}
}

void AAuraPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	//当不是鼠标左键被按住时 可以执行游戏能力
	if(!InputTag.MatchesTagExact(FAuraGameplayTags::Get().InputTag_LMB))
	{
		if(GetASC())
		{
			GetASC()->AbilityInputTagHeld(InputTag);
		}
		return;
	}
	//当thisActor为空指针时执行游戏能力    
    if(bTargeting)
    {
    	if(GetASC())
    	{
    		GetASC()->AbilityInputTagHeld(InputTag);
    	}
    }
	//当以上条件都不满足后,鼠标不瞄准某些东西实现按住 角色移动
    else
    {
	    FollowTime+=GetWorld()->GetDeltaSeconds();
    	
        if(CursirHit.bBlockingHit)
        {
        	 CacheDestination = CursirHit.ImpactPoint;
        }

    	if(APawn* ControllerPawn = GetPawn())
    	{
    		//拿到世界方向
    		const FVector WorldDirection = (CacheDestination - ControllerPawn->GetActorLocation()).GetSafeNormal();
    		ControllerPawn->AddMovementInput(WorldDirection) ;
    	}
    }
}

void AAuraPlayerController::AutoRun()
{

	//判断bAutoRunning=false 时return
	if(!bAutoRunning) return;
	if(APawn* ControllerPawn = GetPawn())
	{
		//获取Pawn最接近样条线的位置
		const  FVector LocationOnSpline = Spline->FindLocationClosestToWorldLocation(ControllerPawn->GetActorLocation(),ESplineCoordinateSpace::World);
		//在样条线上找到与该位置对应的方向
		const FVector Direction = Spline->FindDirectionClosestToWorldLocation(LocationOnSpline,ESplineCoordinateSpace::World);
		ControllerPawn->AddMovementInput(Direction);

		//获得Pawn与目的地的长度
		const float DistanceToDestination = (LocationOnSpline-CacheDestination).Length();

		//判断pawn是否到达半径内
		if(DistanceToDestination<=AutoRunAcceptanceRadius)
		{
			//停止自动运行
			bAutoRunning = false;			
		}
	}

	
}

UAuraAbilitySystemComponent* AAuraPlayerController::GetASC()
{
	if(AuraAbilitySystemComponent==nullptr)
	{
		  AuraAbilitySystemComponent=Cast<UAuraAbilitySystemComponent>
		(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
		
	}

	return  AuraAbilitySystemComponent;
}

void AAuraPlayerController::CursirTrace()
{
	GetHitResultUnderCursor(ECC_Visibility, false, CursirHit);
	if (!CursirHit.bBlockingHit)
		return;

	LastActor = ThisActor;
	ThisActor=Cast<IEnemyInterface>(CursirHit.GetActor());

    if(LastActor!=ThisActor)
    {
	    if(LastActor) LastActor->UnHightlightActor();
    	if(ThisActor) ThisActor->HightlightActor();
    }
	

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
