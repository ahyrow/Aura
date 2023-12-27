// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/AuraHUD.h"
#include "Blueprint/UserWidget.h"
#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "UI/Widgets/AuraUserWidget.h"

void AAuraHUD::BeginPlay()
{
	Super::BeginPlay();
	

}

void AAuraHUD::KOInitOverlay(APlayerController* PC, APlayerState* PS,
	UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	 //检查并打印日志
	 //检查overlayWidget
	checkf(OverlayWidgetClass,TEXT("OverlayWidgetClass Uninitialized,please fill out "));
	checkf(OverlayWidgetControllerClass,TEXT("OverlayWidgetControllerClass Uninitialized,please fill out BP_AuraHUD"))

	//OverlayWidget 强制转换 赋值
	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(),OverlayWidgetClass);
	OverlayWidget = Cast<UAuraUserWidget>(Widget);

	//OverlayWidget与OverlayWidgetController绑定
	const FWidgetControllerParms WidgetControllerParms(PC,PS,ASC,AS);
	UOverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParms);
	OverlayWidget->SetWidgetController(WidgetController);

	//绑定 更新生命值委托
	WidgetController->BroadcastInitiaValues();

	//添加进视口
	OverlayWidget->AddToViewport();
}

UOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(const FWidgetControllerParms& WSParams)
{
	
   if(OverlayWidgetController==nullptr)
   {
       OverlayWidgetController = NewObject<UOverlayWidgetController>(this,OverlayWidgetControllerClass);

   	   OverlayWidgetController->SetWidgetControllerParms(WSParams);

   	   OverlayWidgetController->BindCallbacksToDependcies();
    
   	   return OverlayWidgetController;
   }
  
	
	return OverlayWidgetController;
}

UAttributeMenuWidgetController* AAuraHUD::GetAttributeMenuWidgetController(const FWidgetControllerParms& WSParams)
{
   if(AttributeMenuWidgetController == nullptr)
   {
     AttributeMenuWidgetController=NewObject<UAttributeMenuWidgetController>(this,AttributeMenuWidgetControllerClass);

   	 AttributeMenuWidgetController->SetWidgetControllerParms(WSParams);

   	AttributeMenuWidgetController->BindCallbacksToDependcies();
   }

	return AttributeMenuWidgetController;
}
