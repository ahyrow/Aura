// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AuraCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AbilitySystemComponent.h"
#include <Player\AuraPlayerState.h>
#include <Player/AuraPlayerController.h>
#include <UI/HUD/AuraHUD.h>

AAuraCharacter::AAuraCharacter()
{

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;


}

void AAuraCharacter::PossessedBy(AController* NewController)
{
	 Super::PossessedBy(NewController);
	 
	 InitAbilityActor();

}


void AAuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	InitAbilityActor();


}

void AAuraCharacter::InitAbilityActor()
{
	
	AAuraPlayerState* AuraPlayerState =GetPlayerState<AAuraPlayerState>();

   	check(AuraPlayerState);
	AuraPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(AuraPlayerState,this);
	
	//���� **����ϵͳ** �� **���Լ�** ָ��
	AbilitySystemComponent= AuraPlayerState->GetAbilitySystemComponent();
	AttributeSet = AuraPlayerState->GetAttributeSet();

	//获取AuraHUD
	if(AAuraPlayerController* AuraPlayerController=Cast<AAuraPlayerController>(GetController()))
	{
		AAuraHUD* AuraHUD = Cast<AAuraHUD>(AuraPlayerController->GetHUD());
		if(AuraHUD)
		{
			AuraHUD->InitOverlay(AuraPlayerController, AuraPlayerState, AbilitySystemComponent, AttributeSet);
		}

	}

}
