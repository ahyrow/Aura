// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacter.h"
#include "Interaction/EnemyInterface.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "AuraEnemy.generated.h"


class UWidgetComponent;
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

	//��������ֵ���� ��ͼ�ɷ���
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnMaxHealthChanged;

protected:
	 
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;


protected:
	//AI�ĵȼ�������,ֻ���ķ������ϵļ���
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Character Class Defaults")
	int32 Level=1;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	UWidgetComponent* HealthBar; 
};