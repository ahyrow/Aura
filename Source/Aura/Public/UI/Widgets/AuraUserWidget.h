// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AuraUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraUserWidget : public UUserWidget
{
	GENERATED_BODY()
//
public:
	 UFUNCTION(BlueprintCallable)
	 void SetWidgetController(UObject* InWidgetController);

protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> WidgetController;
protected:
	//��ʼ���ؼ�Ч��
	UFUNCTION(BlueprintImplementableEvent)  //��ͼ��ʵ���¼���
	void WidgetControllerSet();
};