// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AuraEnemy.h"
#include <Aura/Aura.h>
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"

AAuraEnemy::AAuraEnemy()
{
	
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");

	
AbilitySystemComponent -> SetIsReplicated(true);
    AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet=CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");

}
void AAuraEnemy::HightlightActor()
{
	//UE_LOG(LogTemp, Log, TEXT("Hightlight"))

	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	Weapon->SetRenderCustomDepth(true);
	Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);

}

void AAuraEnemy::UnHightlightActor()
{
	//UE_LOG(LogTemp, Log, TEXT("UnHightlight"))
	
	GetMesh()->SetRenderCustomDepth(false);
	Weapon->SetRenderCustomDepth(false);
	
}

void AAuraEnemy::BeginPlay()
{
	Super::BeginPlay();

	AbilitySystemComponent->InitAbilityActorInfo(this , this);
}
