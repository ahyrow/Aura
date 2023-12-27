// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AuraHUD.generated.h"


class UAuraUserWidget;
class UOverlayWidgetController;
class UAbilitySystemComponent;
class UAttributeSet;
class UAttributeMenuWidgetController;
/**
 * 
 */
UCLASS()
class AURA_API AAuraHUD : public AHUD
{
	GENERATED_BODY()
public:

	virtual void BeginPlay() ;
	//视口显示OverlayWidget
	UFUNCTION(BlueprintCallable)
    void InitOverlay(APlayerController* PC,APlayerState* PS,UAbilitySystemComponent* ASC,UAttributeSet* AS);
	

public:
	UFUNCTION()
	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParms& WSParams);

	UFUNCTION()
	UAttributeMenuWidgetController* GetAttributeMenuWidgetController(const FWidgetControllerParms& WSParams);

public:


/*
 *  Attribute Menu
 */
    UPROPERTY(EditAnywhere)
	TSubclassOf<UAttributeMenuWidgetController> AttributeMenuWidgetControllerClass;


	
	/*
	 * Overlay
	 */
	UPROPERTY(EditAnywhere)
	TSubclassOf<UAuraUserWidget>  OverlayWidgetClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;

	
private:

    /*
     * AttributeMenu 控件/控件控制器
     */
	UPROPERTY()
	TObjectPtr<UAttributeMenuWidgetController> AttributeMenuWidgetController;

	
	/*
	 *  Overlap 控件/控件控制器
	 */
    UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;
	
	UPROPERTY()
	TObjectPtr<UAuraUserWidget> OverlayWidget;


};
