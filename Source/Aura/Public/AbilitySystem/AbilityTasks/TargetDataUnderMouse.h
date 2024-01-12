// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "TargetDataUnderMouse.generated.h"

//创建一个多播代表 广播鼠标位置的值
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMouseTargetDataSignature,const FGameplayAbilityTargetDataHandle& ,DataHandle);
/**
 * 
 */
UCLASS()
class AURA_API UTargetDataUnderMouse : public UAbilityTask
{
	GENERATED_BODY()
public:
    //在鼠标下创建目标数据
	/*在GA中调用这个函数的时候 传入this(蓝图中名称是self)*/
	UFUNCTION(BlueprintCallable,Category="Ability|Tasks",
		meta = (DisplayName = "TargetDataUnderMouse",
			HidePin="OwningAbility",
			DefaultToSelf="OwningAbility",
			BlueprintInternalUseOnly="true"))
    static UTargetDataUnderMouse* CreateTargetDataUbderMouse(UGameplayAbility* OwningAbility);

    UPROPERTY(BlueprintAssignable)
	FMouseTargetDataSignature ValidData;

private:
	
	//重写激活事件
	virtual  void Activate() override;
	//发送鼠标光标数据
	void SendMouseCursirData();
	//目标数据复制回调
	void OnTargetDataReplicatedCallback(const FGameplayAbilityTargetDataHandle& DataHandle,FGameplayTag ActivationTag);
};
