// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include "AuraGameplayTags.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"
#include "Chaos/Pair.h"

void UAttributeMenuWidgetController::BindCallbacksToDependcies()
{
	UAuraAttributeSet* AS = Cast<UAuraAttributeSet>(AttributeSet);
	check(AttributeInfo);
	//GetGameplayAttributeValueChangeDelegate()  当属性发生变化时调用的API 返回的是回调函数
	for(auto& Pair : AS->TagsToAttribute )
	{
		//获得Map容器里得Key
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Value()).AddLambda(
	[this,Pair,AS](const FOnAttributeChangeData& Data)
	{
       /*
        //获取属性信息
		FAuraAttributeInfo Info = AttributeInfo->FindAttributeInforTag(Pair.Key);
		Info.AttributeValue = Pair.Value().GetNumericValue(AS);
		//进行广播
		AttributeInfoDelegate.Broadcast(Info);*/
		BroadcastAttributeInfo(Pair.Key,Pair.Value());
	}
	);
	}
}

void UAttributeMenuWidgetController::BroadcastInitiaValues()
{
    
	//先拿到Aura的属性集
	UAuraAttributeSet* AS = Cast<UAuraAttributeSet>(AttributeSet);
	//检查蓝图中的数据资产是否被赋值
	check(AttributeInfo); //声明的数据资产指针由蓝图赋值

	//遍历AS中的Map容器
	for(auto&  Pair : AS->TagsToAttribute)
	{
		/*
		//查找出标签
        FAuraAttributeInfo Info = AttributeInfo->FindAttributeInforTag(Pair.Key);
		//FGameplayAttribute Attr = Pair.Value.Execute();
		//获得标签对应的值
		Info.AttributeValue = Pair.Value().GetNumericValue(AS);
		//进行广播
	  	AttributeInfoDelegate.Broadcast(Info);*/

		BroadcastAttributeInfo(Pair.Key,Pair.Value());
	}
	/*
	 //调用数据资产信息类中的查找标签函数 会返回一个信息的结构体 
	FAuraAttributeInfo StrengthInfo = AttributeInfo->FindAttributeInforTag(FAuraGameplayTags::Get().Attributes_Primary_Strength);
	//通过拿到属性集中的力量值给指定的信息进行同步
	StrengthInfo.AttributeValue = AS->GetStrength();
	//进行广播
	AttributeInfoDelegate.Broadcast(StrengthInfo);
	*/
}

void UAttributeMenuWidgetController::BroadcastAttributeInfo(const FGameplayTag& AttributeTag,
	const FGameplayAttribute& Attribute) const
{
	FAuraAttributeInfo Info = AttributeInfo->FindAttributeInforTag(AttributeTag);
	//FGameplayAttribute Attr = Pair.Value.Execute();
	//获得标签对应的值
	Info.AttributeValue = Attribute.GetNumericValue(AttributeSet);
	//进行广播
	AttributeInfoDelegate.Broadcast(Info);
}
