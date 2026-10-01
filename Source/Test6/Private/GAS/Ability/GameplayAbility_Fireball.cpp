


#include "GAS/Ability/GameplayAbility_Fireball.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffect.h"
#include "AbilitySystemGlobals.h"
#include "GAS/PlayerAttributeSet.h"
#include "Projectile/FireballProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"

UGameplayAbility_Fireball::UGameplayAbility_Fireball()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
}

bool UGameplayAbility_Fireball::CheckCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CheckCost(Handle, ActorInfo, OptionalRelevantTags)) return false;

	UAbilitySystemComponent* ASC = ActorInfo ? ActorInfo->AbilitySystemComponent.Get() : nullptr;
	if (!ASC) return false;

	// 시전자의 현재 Stamina값 가져오기
	const float CurrentStamina = ASC->GetNumericAttribute(UPlayerAttributeSet::GetManaAttribute());

	// 필요 마나량 보다 많아야 실행 가능
	if(CurrentStamina < ManaCost)
		UE_LOG(LogTemp, Display, TEXT("Cannot Use This Ability Now! (low mana)"));

	return CurrentStamina >= ManaCost;
}

void UGameplayAbility_Fireball::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	AActor* Avatar = ActorInfo ? ActorInfo->AvatarActor.Get() : nullptr;
	if (!ProjectileClass || !Avatar)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	// 코스트와 쿨다운 검사 후, 가능하면 적용
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);	// 마지막 true는 정상적인 종료가 아니라는 표시
		return;
	}

	//프로젝타일 소환
	if (!ProjectileClass || !Avatar)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);	// 마지막 true는 정상적인 종료가 아니라는 표시
		return;
	}

	FVector Location = Avatar->GetActorLocation();
	FRotator Rotation = Avatar->GetActorRotation();

	FActorSpawnParameters Params;
	Params.Owner = Avatar;
	Params.Instigator = Cast<APawn>(Avatar);
	Params.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	const FVector SpawnLocation =
		Location + Rotation.Vector() * 100.f;

	if(AFireballProjectile * Projectile = GetWorld()->SpawnActor<AFireballProjectile>(ProjectileClass, SpawnLocation, Rotation, Params))
	{
		// 충돌 없으면 3초뒤 삭제
		Projectile->SetLifeSpan(3.f);
		if (UProjectileMovementComponent* ProjectileMovement = Projectile->FindComponentByClass<UProjectileMovementComponent>())
		{
			ProjectileMovement->SetUpdatedComponent(Projectile->GetRootComponent());
			ProjectileMovement->ProjectileGravityScale = 0.f;
			ProjectileMovement->InitialSpeed = ProjectileSpeed;
			ProjectileMovement->MaxSpeed = ProjectileSpeed;
			ProjectileMovement->Velocity = Rotation.Vector() * ProjectileSpeed;
		}
	}

	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);

}

