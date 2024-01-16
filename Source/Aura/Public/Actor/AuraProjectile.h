// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "GameFramework/Actor.h"
#include "AuraProjectile.generated.h"

class UProjectileMovementComponent;
class USphereComponent;
class UNiagaraSystem;
class UAudioComponent;

UCLASS()
class AURA_API AAuraProjectile : public AActor
{
	GENERATED_BODY()
public:	
	AAuraProjectile();

public:
    //创建一个弹体组件
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;

	//
	UPROPERTY(BlueprintReadWrite,meta=(ExposeOnSpawn=true))
	FGameplayEffectSpecHandle DamageEffectSpecHandle;
protected:
	
	virtual void BeginPlay() override;

	virtual void Destroyed() override;

	//球体的重叠事件
	UFUNCTION()
	void OnSphereOverlap
	(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
   
private:

	UPROPERTY(EditDefaultsOnly)
	float LifeSPan = 15.f;

	//是否碰撞
     bool bHit = false;
	
    //创建球体组件
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> Sphere;

	//碰撞效果
    UPROPERTY(EditAnywhere)
	TObjectPtr<UNiagaraSystem> ImpactEffect;
	//碰撞音效
	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase>   ImpactSound;

	//循环音效
	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase> LoopingSound;

	//音效组件
	UPROPERTY()
	TObjectPtr<UAudioComponent> LoopingSoundComponent;
};
