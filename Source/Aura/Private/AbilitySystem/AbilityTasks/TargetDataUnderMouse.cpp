// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AbilityTasks/TargetDataUnderMouse.h"
#include "AbilitySystemComponent.h"

UTargetDataUnderMouse* UTargetDataUnderMouse::CreateTargetDataUbderMouse(UGameplayAbility* OwningAbility)
{
	
   UTargetDataUnderMouse* MyObj = NewAbilityTask<UTargetDataUnderMouse>(OwningAbility) ;


	return MyObj;
}

void UTargetDataUnderMouse::Activate()
{
	//检查是否受本地控制
	const bool bIsLocallyControlled = Ability->GetCurrentActorInfo()->IsLocallyControlled();
    if(bIsLocallyControlled)
    {
    	//如果为ture  发送鼠标光标数据
	    SendMouseCursirData();
    }
    else
    {
    	const FGameplayAbilitySpecHandle SpecHandle = GetAbilitySpecHandle();
    	const FPredictionKey ActivationPredictionKey = GetActivationPredictionKey();
	    //如果是false 说明在服务器上,所以需要监听目标数据是否到达
      AbilitySystemComponent.Get()->AbilityTargetDataSetDelegate(
      	SpecHandle,
      	ActivationPredictionKey).
    	AddUObject(this,&UTargetDataUnderMouse::OnTargetDataReplicatedCallback);
         //判断是否广播
    	const bool bCalledDelegate = AbilitySystemComponent->CallReplicatedTargetDataDelegatesIfSet(SpecHandle,ActivationPredictionKey);
    	if(!bCalledDelegate)
    	{
    		//等待玩家数据
    		SetWaitingOnRemotePlayerData();
    	}
    }

}

void UTargetDataUnderMouse::SendMouseCursirData()
{
	
	/** 获取鼠标光标的位置并发送 */

    //代码预测??
	FScopedPredictionWindow ScopedPredictionWindow(AbilitySystemComponent.Get());

	//拿到PC
	APlayerController* PC =Ability->GetCurrentActorInfo()->PlayerController.Get();
	if(PC)
	{
		FHitResult CursorHit;
		PC->GetHitResultUnderCursor(ECC_Visibility,false,CursorHit);

		FGameplayAbilityTargetDataHandle DataHandle;
		FGameplayAbilityTargetData_SingleTargetHit* Data = new FGameplayAbilityTargetData_SingleTargetHit();
		Data->HitResult = CursorHit;
		//将目标数据添加到数据句柄中
		DataHandle.Add(Data);

		
		//ServerSetReplicatedTargetData() 将目标数据发送到服务器
		AbilitySystemComponent->ServerSetReplicatedTargetData(
			GetAbilitySpecHandle(),
			GetActivationPredictionKey(),
			DataHandle,
			FGameplayTag(),
			AbilitySystemComponent->ScopedPredictionKey);
       //先判断一下能力是否处于活动状态
		if(ShouldBroadcastAbilityTaskDelegates())
		{
			//进行广播
			ValidData.Broadcast(DataHandle);
		}
	}
	
}

void UTargetDataUnderMouse::OnTargetDataReplicatedCallback(const FGameplayAbilityTargetDataHandle& DataHandle,
	FGameplayTag ActivationTag)
{
	//调用ConsumeClientReplicatedTargetData()API  表示已经收到数据 
	 AbilitySystemComponent->ConsumeClientReplicatedTargetData(GetAbilitySpecHandle(),GetActivationPredictionKey());
	//
	if(ShouldBroadcastAbilityTaskDelegates())
	{
		//进行广播
		ValidData.Broadcast(DataHandle);
	}
}


