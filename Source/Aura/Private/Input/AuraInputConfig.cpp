// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/AuraInputConfig.h"

#include "InputAction.h"

const UInputAction* UAuraInputConfig::FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound)
{
    for(const  FAuraInputAction& Action: AbilityInputActions)
    {
    	if(Action.InputAction && Action.InputTag == InputTag )
    	{
    		return Action.InputAction;
    	}
    	
    }
    if(bLogNotFound)
    {
    	UE_LOG(LogTemp,Error,TEXT("没有找到标签对应的能力输入[%s] , 输入配置[%s]"),*InputTag.ToString(),*GetNameSafe(this));
    }
	
	return  nullptr;
}
