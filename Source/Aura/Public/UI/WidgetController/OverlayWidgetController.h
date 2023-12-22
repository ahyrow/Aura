// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "UI/Widgets/AuraUserWidget.h"
#include "OverlayWidgetController.generated.h"

class UAuraWidgetController;


//���ݵ��߶���ı�ǩ ��UI����Ӧ��������ʾ����Ļ
USTRUCT(BlueprintType)
struct FUIWidgetRow:public FTableRowBase
{
	GENERATED_BODY()
	//��Ϸ��ǩ
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	FGameplayTag MessageTag = FGameplayTag(); 

	//������Ϣ
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	FText Message = FText();

	//������ʾ�Ŀؼ�
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TSubclassOf<UAuraUserWidget> MessageWidget;
	
	//���߶���ͼƬ
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	UTexture2D* Image = nullptr ; 
	
};


/**
 * 
 */

//�����ಥ����
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChangedSignature, float ,NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMessageWidgetRowSignature,FUIWidgetRow, Row);


UCLASS(BlueprintType,Blueprintable)
class AURA_API UOverlayWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()


public:

	virtual void BroadcastInitiaValues() override;
	virtual void  BindCallbacksToDependcies() override;
	
	//��������
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes") //��ͼ�ɷ���
	FOnAttributeChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes") //��ͼ�ɷ���
	FOnAttributeChangedSignature OnMaxHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes") //��ͼ�ɷ���
	FOnAttributeChangedSignature OnManaChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes") //��ͼ�ɷ���
	FOnAttributeChangedSignature OnMaxManaChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Massages") 
	FMessageWidgetRowSignature MessageWidgetRowSignature; 

protected:
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Widget Data")
    TObjectPtr<UDataTable> MessageDataTable;
	
	//����������
	template<typename T>
	T*  GetDataTableRowByTag(UDataTable* DataTable,FGameplayTag& Tag);
};

template <typename T>
T* UOverlayWidgetController::GetDataTableRowByTag(UDataTable* DataTable, FGameplayTag& Tag)
{
	//���ر�ͷ
	T* Row =DataTable->FindRow<T>(Tag.GetTagName(),TEXT(""));
	if(Row)
	{
		return Row;
	}
	return nullptr;
}
