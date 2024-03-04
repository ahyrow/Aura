// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/AuraProjectileSpell.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Actor/AuraProjectile.h"
#include "Interaction/CombatInterface.h"
#include "Aura/public/AuraGameplayTags.h"
#include "Kismet/KismetSystemLibrary.h"

void UAuraProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                           const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                           const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	
	
}

void UAuraProjectileSpell::SpawnProjectile(const FVector& ProjectileTargetLoacation)
{
	
	//如果是服务器的话返回true
		const bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();
		//如果不在服务器  return
		if(!bIsServer) return;

		//根据拥有这类能力的Character  拿到战斗接口     
		ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo());

	if(CombatInterface)
	{
		//拿到武器插槽位置
		const FVector SocketLocation = CombatInterface->GetCombatSocketLocation();
		//目标位置与武器插槽位置之间的向量
		FRotator Rotator = (ProjectileTargetLoacation - SocketLocation).Rotation();
		//Pitch值归0
		Rotator.Pitch =0.f;
		
		//生成AuraProjectile	
		FTransform SpawnTransform;
		//在武器插槽位置生成
		SpawnTransform.SetLocation(SocketLocation );
		//设置方向
		SpawnTransform.SetRotation(Rotator.Quaternion());
	
		AAuraProjectile* Projectile = GetWorld()->SpawnActorDeferred<AAuraProjectile>
		(ProjectileClass,
			SpawnTransform,
			GetOwningActorFromActorInfo(),
			Cast<APawn>(GetOwningActorFromActorInfo()),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

		//Projectile造成伤害
		/*
		 * Make Effect Spec Handle
		 */
		UAbilitySystemComponent* SourceASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetAvatarActorFromActorInfo());
		FGameplayEffectSpecHandle SpecHandle = SourceASC->MakeOutgoingSpec(DamageEffectClass,GetAbilityLevel(),SourceASC->MakeEffectContext());  

        FAuraGameplayTags GameplayTags = FAuraGameplayTags::Get();
		//获得伤害值   Damage.GetValueAtLevel(GetAbilityLevel())
		const float ScaledDamage = Damage.GetValueAtLevel(GetAbilityLevel());
		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude( SpecHandle,GameplayTags.Damage,ScaledDamage);
		Projectile->DamageEffectSpecHandle = SpecHandle;

		Projectile->FinishSpawning(SpawnTransform);
	}
}
