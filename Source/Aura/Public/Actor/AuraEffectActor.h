// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ActiveGameplayEffectHandle.h"
#include "AuraEffectActor.generated.h"

class UAbilitySystemComponent;

//����Ч��
UENUM(BlueprintType)
enum class EEffectApplicationPolicy
{
	ApplyOverlap,
	ApplyOnEndOverlap,
	//������
	DoNotApply
};
//�Ƴ�Ч��
UENUM(BlueprintType)
enum class EEffectRemoverPolicy
{
	RemoveOnEndOverlap,
	DoNotRemove
};


class UGameplayEffect;
UCLASS()
class AURA_API AAuraEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AAuraEffectActor();

	//����ͼ���
	/*UFUNCTION()
	virtual void OnOverlap(UPrimitiveComponent* OverlappedComponent, 
		AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, 
		bool bFromSweep, 
		const FHitResult& SweepResult);
	UFUNCTION()
	virtual void EndOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex
		);*/
protected:
	
	virtual void BeginPlay() override;
	

protected:

	 //��Ŀ��ʩ��Ч��
	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(AActor* ActorTarget,TSubclassOf<UGameplayEffect> GameplayEffectClass);

    //
	UFUNCTION(BlueprintCallable)
	void OnOverlap(AActor* TargetActor);

	//
	UFUNCTION(BlueprintCallable)
	void OnEndOverlap(AActor* TargetActor);
	
	//˲��Ч����
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Applid Effects")
	TSubclassOf<UGameplayEffect> InstantGamePlayEffectClass;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Applid Effects")
	EEffectApplicationPolicy InstantEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;
	//����ʱ��Ч����
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Applid Effects")
	TSubclassOf<UGameplayEffect> DurationGamePlayEffectClass;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Applid Effects")
	EEffectApplicationPolicy DurationEffectApplicationPolicy=EEffectApplicationPolicy::DoNotApply ;
    //����Ч���� 
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Applid Effects")
	TSubclassOf<UGameplayEffect> InfinitGamePlayEffectClass;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Applid Effects")
	EEffectApplicationPolicy InfinitEffectApplicationPolicy =EEffectApplicationPolicy::DoNotApply;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Applid Effects")
	EEffectRemoverPolicy InfinitEffectRemovePolicy=EEffectRemoverPolicy::RemoveOnEndOverlap;

    TMap<FActiveGameplayEffectHandle, UAbilitySystemComponent*>  ActiveEffectHandles;

protected:
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Applid Effects")
	float ActorLevel = 1.f;
};
