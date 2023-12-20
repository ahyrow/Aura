// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/AuraEffectActor.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayEffect.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"

AAuraEffectActor::AAuraEffectActor()
{
 	
	PrimaryActorTick.bCanEverTick = false;

    SetRootComponent(CreateDefaultSubobject<USceneComponent>("Scene"));
}



void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();


}

void AAuraEffectActor::ApplyEffectToTarget(AActor* ActorTarget, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	//���ش�Target������ϵͳ���
	UAbilitySystemComponent*  TargetASC =	UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(ActorTarget);
	//���TargetASCΪ�� return
    if(TargetASC == nullptr) return;

	check(GameplayEffectClass);
	FGameplayEffectContextHandle EffectContextHandle =TargetASC->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this); 
    const FGameplayEffectSpecHandle EffectSpecHandle=TargetASC->MakeOutgoingSpec(GameplayEffectClass,1.f,EffectContextHandle)	;
    //�洢 Ч������
	const FActiveGameplayEffectHandle ActiveGameplayEffectHandle=TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());

	//�жϵ�ǰ�����Ч������  Ӧ�õ��ǲ�������Ч��
	const bool bIsInfinite= EffectSpecHandle.Data.Get()->Def.Get()->DurationPolicy == EGameplayEffectDurationType::Infinite;
    //�����ǰ�����Ч������ Ӧ�õ�������Ч�� ���� ��ǰӦ�õ����Ƴ��ص�
	if(bIsInfinite && InfinitEffectRemovePolicy==EEffectRemoverPolicy::RemoveOnEndOverlap)
	{
		//�洢��Ч���ľ�� ������Ч��
		ActiveEffectHandles.Add(ActiveGameplayEffectHandle,TargetASC);
		 
	}

}

void AAuraEffectActor::OnOverlap(AActor* TargetActor)
{
	if(InstantEffectApplicationPolicy  == EEffectApplicationPolicy::ApplyOverlap)
	{

		ApplyEffectToTarget(TargetActor,InstantGamePlayEffectClass);
	}
	if(DurationEffectApplicationPolicy ==EEffectApplicationPolicy::ApplyOverlap)
	{
		ApplyEffectToTarget(TargetActor,DurationGamePlayEffectClass);
	}
	if(InfinitEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOverlap)
	{

		ApplyEffectToTarget(TargetActor,InfinitGamePlayEffectClass);
	}
}

void AAuraEffectActor::OnEndOverlap(AActor* TargetActor)
{

	if(InstantEffectApplicationPolicy  == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor,InstantGamePlayEffectClass);
	}
	if(DurationEffectApplicationPolicy ==EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor,DurationGamePlayEffectClass);
	}
	if(InfinitEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{

		ApplyEffectToTarget(TargetActor,InfinitGamePlayEffectClass);
	}
	if(InfinitEffectRemovePolicy == EEffectRemoverPolicy::RemoveOnEndOverlap)
	{
		UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
		if(!IsValid(TargetASC)) return;

		
        TArray<FActiveGameplayEffectHandle> HandlesToRemove;
		for (TTuple<FActiveGameplayEffectHandle, UAbilitySystemComponent*>  HandlePair : ActiveEffectHandles)
		{
          if(TargetASC == HandlePair.Value )
          {
              //�������ϵͳ����뵱ǰMap�����е�ֵ���   �����ϷЧ��
          	TargetASC->RemoveActiveGameplayEffect(HandlePair.Key);
          	HandlesToRemove.Add(HandlePair.Key);
          }
			
		}
		for(FActiveGameplayEffectHandle& Handles  : HandlesToRemove)
		{

			ActiveEffectHandles.FindAndRemoveChecked(Handles);
		}
	}
	
}


