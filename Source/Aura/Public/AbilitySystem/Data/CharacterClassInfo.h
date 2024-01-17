// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

 #include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CharacterClassInfo.generated.h"

class UGameplayEffect;
//创建角色类枚举
UENUM(BlueprintType)
enum class ECharacterClass:uint8
{
	Elementalist,
	Warrior,
	Ranger
	
};
//创建结构体存储角色信息
USTRUCT(BlueprintType)
struct FCharacterClassDefaultInfo
{
    GENERATED_BODY()
	//主属性
	UPROPERTY(EditDefaultsOnly,Category= "Class Defaults")
	TSubclassOf<UGameplayEffect> PrimaryAttributes;
	
};
/**
 * 
 */
UCLASS()
class AURA_API UCharacterClassInfo : public UDataAsset
{
	GENERATED_BODY()
public:
	
   //使用Tmap来映射 角色类对应的角色信息
	UPROPERTY(EditDefaultsOnly,Category= "Character Class Defaults")
	TMap<ECharacterClass,FCharacterClassDefaultInfo> CharacterClassInfomation;
	
	UPROPERTY(EditDefaultsOnly,Category= "Common Class Defaults")
	TSubclassOf<UGameplayEffect> SecondaryAttributes;
	
	UPROPERTY(EditDefaultsOnly,Category= "Common Class Defaults")
	TSubclassOf<UGameplayEffect> VitalAttributes;

	//查询
	FCharacterClassDefaultInfo GetClassDefaultInfo( ECharacterClass CharacterClass);
};
