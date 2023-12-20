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
	//返回此Target的能力系统组件
	UAbilitySystemComponent*  TargetASC =	UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(ActorTarget);
	//如果TargetASC为空 return
    if(TargetASC == nullptr) return;

	check(GameplayEffectClass);
	FGameplayEffectContextHandle EffectContextHandle =TargetASC->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this); 
    const FGameplayEffectSpecHandle EffectSpecHandle=TargetASC->MakeOutgoingSpec(GameplayEffectClass,1.f,EffectContextHandle)	;
    //存储 效果数据
	const FActiveGameplayEffectHandle ActiveGameplayEffectHandle=TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());

	//判断当前对象的效果数据  应用的是不是永久效果
	const bool bIsInfinite= EffectSpecHandle.Data.Get()->Def.Get()->DurationPolicy == EGameplayEffectDurationType::Infinite;
    //如果当前对象的效果数据 应用的是永久效果 并且 当前应用的是移除重叠
	if(bIsInfinite && InfinitEffectRemovePolicy==EEffectRemoverPolicy::RemoveOnEndOverlap)
	{
		//存储该效果的句柄 来消除效果
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
              //如果能力系统组件与当前Map容器中的值相等   清除游戏效果
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


