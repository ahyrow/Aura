// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Data/AttributeInfo.h"

FAuraAttributeInfo UAttributeInfo::FindAttributeInforTag(const FGameplayTag& AttributeTag, bool blogNotFound) const
{

    //如何在数组中找到属性信息结构
	      //for里面可以替换 Info.AttributeTag.MatchesTagExact(AttributeTag) 精准查找
	for(const FAuraAttributeInfo& Info : AttributeInformation)
	{
     if(Info.AttributeTag==AttributeTag)
     {
     	return Info;
     }		
	}
 
	if(blogNotFound)
	{
		UE_LOG(LogTemp,Error,TEXT("没有找到属性标签[%s] ,属性标签信息 [%s]"),*AttributeTag.ToString(),*GetNameSafe(this));
	}
	return FAuraAttributeInfo();
}
