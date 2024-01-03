// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor\AuraProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AAuraProjectile::AAuraProjectile()
{
	PrimaryActorTick.bCanEverTick =false;
	bReplicates = true;

	/*
	 * SphereComponent
	 */
	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	SetRootComponent(Sphere);
	Sphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Sphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	Sphere->SetCollisionResponseToChannel(ECC_WorldDynamic,ECR_Overlap);
	Sphere->SetCollisionResponseToChannel(ECC_WorldStatic,ECR_Overlap);
	Sphere->SetCollisionResponseToChannel(ECC_Pawn,ECR_Overlap);

	/*
	 * ProjectileMovementComponent
	 */
     ProjectileMovement= CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	//设置初始速度
	ProjectileMovement->InitialSpeed = 550.f;
	//设置最大速度
	ProjectileMovement->MaxSpeed = 550.f;
	//设置重力
	ProjectileMovement->ProjectileGravityScale = 0.f;
	
	
}


void AAuraProjectile::BeginPlay()
{
	Super::BeginPlay();
	Sphere->OnComponentBeginOverlap.AddDynamic(this,&AAuraProjectile::OnSphereOverlap);
}

void AAuraProjectile::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}



