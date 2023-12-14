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
	//初始化控件效果
	UFUNCTION(BlueprintImplementableEvent)  //    在蓝图实现事件 在C++里调用
	void WidgetControllerSet();
};
