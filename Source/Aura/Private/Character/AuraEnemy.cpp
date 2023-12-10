// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AuraEnemy.h"
#include <Aura/Aura.h>

AAuraEnemy::AAuraEnemy()
{
	
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

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
