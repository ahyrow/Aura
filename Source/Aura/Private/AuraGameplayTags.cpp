// Fill out your copyright notice in the Description page of Project Settings.


#include "AuraGameplayTags.h"
#include "GameplayTagsManager.h"
//创建静态游戏标记实例
FAuraGameplayTags FAuraGameplayTags::GameplayTags;


void FAuraGameplayTags::InitializeNatveGameplayTags()
{
	/*
	 * Primary Attributes
	 */
	GameplayTags.Attributes_Primary_Strength=
	 UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Strength"),FString("Increases physical damage"));

	GameplayTags.Attributes_Primary_Intelligence=
	 UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Intelligence"),FString("Increases magical damage"));

	GameplayTags.Attributes_Primary_Resilience=
	 UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Resilience"),FString("Increases Armor and Armor Penetratior"));

	GameplayTags.Attributes_Primary_Vigor=
	 UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Vigor"),FString("Increases Health"));


/*
 * Secondary Attributes
 */
	
	GameplayTags.Attributes_Secondary_Armor=
 	UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.Armor"),FString("Reduces damage taken, improves Block chance"));
	
	GameplayTags.Attributes_Secondary_ArmorPenetration=
		UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.ArmorPenetration"),FString("Ignored Percentage of enemy Armor,increases Critical Hit Chance"));

	GameplayTags.Attributes_Secondary_BlockChance=
	 UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.BlockChance"),FString("Chance to cut incoming damage in half"));

	GameplayTags.Attributes_Secondary_CriticalHitChance=
    UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CriticalHitChance"),FString("Chance to double damage plus critical bonusf"));

	GameplayTags.Attributes_Secondary_CriticalHitDamage=
		UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CriticalHitDamage"),FString("Bonus admage added when a critical hit is scored"));

	GameplayTags.Attributes_Secondary_CriticalHitResistance=
		UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CriticalHitResistance"),FString("Reduces Critical Hit chance of attacking enemies"));

	GameplayTags.Attributes_Secondary_HealthRegeneration=
		UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.HealthRegeneration"),FString("Amount of Health regeneated every 1 second"));

	GameplayTags.Attributes_Secondary_ManaRegeneration=
			UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.ManaRegeneration"),FString("Amount of Mana regeneated every 1 second"));

	GameplayTags.Attributes_Secondary_MaxHealth=
				UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MaxHealth"),FString("Maximum amount of Health obtainable"));

	GameplayTags.Attributes_Secondary_MaxMana=
				UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MaxMana"),FString("Maximum amount of Mana obtainable"));

}
