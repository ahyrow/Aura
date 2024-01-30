// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AuraCharacterBase.h"

#include "AbilitySystemComponent.h"
#include "ShaderPrintParameters.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Aura/Aura.h"
#include "Components/CapsuleComponent.h"

AAuraCharacterBase::AAuraCharacterBase()
{
	PrimaryActorTick.bCanEverTick =false;

	/*
	 * CapsuleComponent
	 */
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera,ECR_Ignore);
	GetCapsuleComponent()->SetGenerateOverlapEvents(false);

	/*
	 * Mesh
	 */
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera,ECR_Ignore);
	//修改自定义碰撞检测并生成重叠事件
	GetMesh()->SetCollisionResponseToChannel(ECC_Projectile,ECR_Overlap);
    GetMesh()->SetGenerateOverlapEvents(true);

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("L_Hand_WeaponSocket"));   //(GetMesh(), FName("L_Hand_WeaponSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

UAbilitySystemComponent* AAuraCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}


UAnimMontage* AAuraCharacterBase::GetHitReactMontage_Implementation()
{ 
  return  HitReactMontage; 
}

// Called when the game starts or when spawned
void AAuraCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

void AAuraCharacterBase::InitAbilityActorInfo()
{
}

FVector AAuraCharacterBase::GetCombatSocketLocation()
{
	//根据武器插槽名称获得插槽位置
	return Weapon->GetSocketLocation(WeaponTipSocketName);
}

void AAuraCharacterBase::Die()
{
	//武器脱手
	Weapon->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepWorld,true));
	MulticastHandleDeath();
}

void AAuraCharacterBase::MulticastHandleDeath_Implementation()
{
	/*
	 * 死亡后的散落效果
	 */

	/*
	 * 武器
	 */
	//开启模拟物理
	Weapon->SetSimulatePhysics(true);
	//启用重力
	Weapon->SetEnableGravity(true);
	//启用碰撞
	Weapon->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);

	/*
	 * Mesh
	 */
	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetEnableGravity(true);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	GetMesh()->SetCollisionResponseToChannel(ECC_WorldStatic,ECR_Block);
    GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	/*
	 * 溶解效果
	 */
	Dissolve();
}


void AAuraCharacterBase::InitializeDefaultAttributes() const
{
    ApplyEffectToSelf(DefaultPrimaryAttributes,1.f);
	ApplyEffectToSelf(DefaultSecondaryAttributes,1.f);
	ApplyEffectToSelf(DefaultVitalAttributes,1.f);
}

void AAuraCharacterBase::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectclass, float Level) const
{


	check(IsValid(GetAbilitySystemComponent()))
    check(GameplayEffectclass);
	//GamneplayEffect?????ASC
	FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	//如何设置源对象
	ContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(GameplayEffectclass,Level,ContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(),GetAbilitySystemComponent());
}

void AAuraCharacterBase::AddCharacterAbilities()
{
	UAuraAbilitySystemComponent* AuraASC = CastChecked<UAuraAbilitySystemComponent>(AbilitySystemComponent);
	//如果没有权力 就返回
	 if(!HasAuthority()) return;
	//调用ASC中封装的给予能力函数
	AuraASC->AddCharacterAbilities(StartupAbilities);
}

void AAuraCharacterBase::Dissolve()
{
	if(IsValid(DissolveMaterrialInstance))
	{
		//创建动态材质
		UMaterialInstanceDynamic* DynamicInstance = UMaterialInstanceDynamic::Create(DissolveMaterrialInstance,this);
		//赋值给Mesh
		GetMesh()->SetMaterial(0,DynamicInstance);
        //溶解时长
		StartDissolveTimeLine(DynamicInstance);
		
	}
	if(IsValid(WeaponDissolveMaterrialInstance))
	{
         
		//创建动态材质
		UMaterialInstanceDynamic* DynamicInstance = UMaterialInstanceDynamic::Create(WeaponDissolveMaterrialInstance,this);
		//赋值给Mesh
		Weapon->SetMaterial(0,DynamicInstance );
		//溶解时长
		StartWeaponDissolveTimeLine(DynamicInstance);
	} 
	
}




