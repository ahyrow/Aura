// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacter.h"
#include "Interaction/EnemyInterface.h"
#include "AuraEnemy.generated.h"


/**
 * 
 */
UCLASS()
class AURA_API AAuraEnemy : public AAuraCharacterBase , public  IEnemyInterface
{
	GENERATED_BODY()
public:
	AAuraEnemy();
	
   /**Enemy Interface**/
	virtual void HightlightActor() override;
	virtual void UnHightlightActor() override;
   /** end Enemy Interface**/

	/** Combat Interface */
	virtual int32 GetPlayerLevel() override;
	/** End Combat Interface */

protected:
	 
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;


protected:
	//AI的等级不复制,只关心服务器上的级别
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Character Class Defaults")
	int32 Level=1;
};