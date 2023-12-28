// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/AttributeMenuWidgetController.h"

#include "AuraGameplayTags.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"

void UAttributeMenuWidgetController::BindCallbacksToDependcies()
{
	
}

void UAttributeMenuWidgetController::BroadcastInitiaValues()
{
    
	//先拿到Aura的属性集
	UAuraAttributeSet* AS = Cast<UAuraAttributeSet>(AttributeSet);
	//检查蓝图中的数据资产是否被赋值
	check(AttributeInfo); //声明的数据资产指针由蓝图赋值

	//调用数据资产信息类中的查找标签函数 会返回一个信息的结构体 
	FAuraAttributeInfo Info = AttributeInfo->FindAttributeInforTag(FAuraGameplayTags::Get().Attributes_Primary_Strength);
	//通过拿到属性集中的力量值给指定的信息进行同步
	Info.AttributeValue = AS->GetStrength();
	//进行广播
	AttributeInfoDelegate.Broadcast(Info);
}
