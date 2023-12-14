// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/AuraWidgetController.h"

void UAuraWidgetController::SetWidgetControllerParms(const FWidgetControllerParms& WCParms)
{
	PlayerController = WCParms.PlayerController;
	PlayerState = WCParms.PlayerState;
	AbilitySystemComponent = WCParms.AbilitySystemComponent;
	AttributeSet = WCParms.AttributeSet;

	
}

void UAuraWidgetController::BroadcastInitiaValues()
{
}

void UAuraWidgetController::BindCallbacksToDependcies()
{
}
