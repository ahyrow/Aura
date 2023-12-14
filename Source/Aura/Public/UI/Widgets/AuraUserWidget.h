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
//k
public:
	 UFUNCTION(BlueprintCallable)
	 void SetWidgetController(UObject* InWidgetController);

protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> WidgetController;
protected:
	//��ʼ���ؼ�Ч��
	UFUNCTION(BlueprintImplementableEvent)  //    ����ͼʵ���¼� ��C++�����
	void WidgetControllerSet();
};
