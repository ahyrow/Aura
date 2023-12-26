// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "UI/Widgets/AuraUserWidget.h"
#include "OverlayWidgetController.generated.h"

class UAuraWidgetController;


//根据道具对象的标签 给UI传对应的数据显示在屏幕
USTRUCT(BlueprintType)
struct FUIWidgetRow:public FTableRowBase
{
	GENERATED_BODY()
	//游戏标签
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	FGameplayTag MessageTag = FGameplayTag(); 

	//文字信息
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	FText Message = FText();

	//创建显示的控件
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TSubclassOf<UAuraUserWidget> MessageWidget;
	
	//道具对象图片
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	UTexture2D* Image = nullptr ; 
	
};


/**
 * 
 */

//声明多播代理
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChangedSignature, float ,NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMessageWidgetRowSignature,FUIWidgetRow, Row);


UCLASS(BlueprintType,Blueprintable)
class AURA_API UOverlayWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()


public:

	virtual void BroadcastInitiaValues() override;
	virtual void  BindCallbacksToDependcies() override;
	
	//创建代理
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes") //蓝图可分配
	FOnAttributeChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes") //蓝图可分配
	FOnAttributeChangedSignature OnMaxHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes") //蓝图可分配
	FOnAttributeChangedSignature OnManaChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes") //蓝图可分配
	FOnAttributeChangedSignature OnMaxManaChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Massages") 
	FMessageWidgetRowSignature MessageWidgetRowSignature; 

protected:
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Widget Data")
    TObjectPtr<UDataTable> MessageDataTable;
	
	//返回数据行
	template<typename T>
	T*  GetDataTableRowByTag(UDataTable* DataTable,FGameplayTag& Tag);
};

template <typename T>
T* UOverlayWidgetController::GetDataTableRowByTag(UDataTable* DataTable, FGameplayTag& Tag)
{
	//返回表头
	T* Row =DataTable->FindRow<T>(Tag.GetTagName(),TEXT(""));
	if(Row)
	{
		return Row;
	}
	return nullptr;
}
