// Fill out your copyright notice in the Description page of Project Settings.


#include "AuraAssetManager.h"
#include"AuraGameplayTags.h"
#include "AbilitySystemGlobals.h"

UAuraAssetManager& UAuraAssetManager::Get()
{
    check(GEngine)
	UAuraAssetManager* AuraAssetManager=Cast<UAuraAssetManager>(GEngine->AssetManager);
	return   *AuraAssetManager;
}

void UAuraAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
    FAuraGameplayTags::InitializeNatveGameplayTags();
	//使用TargetData 的必要条件
	UAbilitySystemGlobals::Get().InitGlobalData();
}
