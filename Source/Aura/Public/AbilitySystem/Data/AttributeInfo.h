// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "AttributeInfo.generated.h"

USTRUCT(BlueprintType)
struct FAuraAttributeInfo
{
	GENERATED_BODY()
	//使用标签来识别属性
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
    FGameplayTag AttributeTag = FGameplayTag();

	//属性名称
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FText AttributeName = FText();
	//属性描述
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FText AttributeDescription = FText();
	//属性值 不在数据资产中编辑 在广播前设置值
	UPROPERTY(BlueprintReadOnly)
	float AttributeValue = 0.f;
	
};




/**
 * 
 */
UCLASS()
class AURA_API UAttributeInfo : public UDataAsset
{
	GENERATED_BODY()
	
public:
	//封装函数 传入游戏标签返回属性信息
    FAuraAttributeInfo FindAttributeInforTag(const FGameplayTag& AttributeTag,bool blogNotFound = false) const;
	
	//创建数组存储属性信息结构
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TArray<FAuraAttributeInfo> AttributeInformation;
	
};
