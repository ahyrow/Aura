// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AuraEnemy.h"
#include <Aura/Aura.h>
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Components/WidgetComponent.h"

AAuraEnemy::AAuraEnemy()
{

    
	
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
    AbilitySystemComponent -> SetIsReplicated(true);
    AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet=CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");

    //创建Bar控件组件
	HealthBar= CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBar"));
	HealthBar->SetupAttachment(GetRootComponent());
}
void AAuraEnemy::HightlightActor()
{
	//UE_LOG(LogTemp, Log, TEXT("Hightlight"))

	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	Weapon->SetRenderCustomDepth(true);
	Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);

}

void AAuraEnemy::UnHightlightActor()
{
	//UE_LOG(LogTemp, Log, TEXT("UnHightlight"))
	
	GetMesh()->SetRenderCustomDepth(false);
	Weapon->SetRenderCustomDepth(false);
	
}

int32 AAuraEnemy::GetPlayerLevel()
{
	return Level;
}

void AAuraEnemy::BeginPlay()
{
	Super::BeginPlay();
	InitAbilityActorInfo();


	//给BarWidget赋值
	if(UAuraUserWidget* AuraUserWidget = Cast<UAuraUserWidget>(HealthBar->GetUserWidgetObject()))
	{
		AuraUserWidget->SetWidgetController(this);
	}
	//绑定生命值代理
	//拿到属性集
	UAuraAttributeSet* AuraAS = Cast<UAuraAttributeSet>(AttributeSet);
	if(AuraAS)
	{
       AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAS->GetHealthAttribute()).AddLambda(
       	[this](const FOnAttributeChangeData& Data)
       {
	     OnHealthChanged.Broadcast(Data.NewValue);  
       });
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAS->GetMaxHealthAttribute()).AddLambda(
		   [this](const FOnAttributeChangeData& Data)
	   {
		 OnMaxHealthChanged.Broadcast(Data.NewValue);  
	   });
      //广播初始值
		OnHealthChanged.Broadcast(AuraAS->GetHealth());
		OnMaxHealthChanged.Broadcast(AuraAS->GetMaxHealth());
	}
}

void AAuraEnemy::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this , this);
	UAuraAbilitySystemComponent* AuraAbilitySystemComponent=Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent);
	if(AuraAbilitySystemComponent)
	{
		AuraAbilitySystemComponent->AbilityActorInfoSet();
	}

	InitializeDefaultAttributes();
}
