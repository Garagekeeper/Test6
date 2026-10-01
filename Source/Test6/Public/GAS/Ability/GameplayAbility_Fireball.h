

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GameplayAbility_Fireball.generated.h"

class AFireballProjectile;

/**
 * 
 */
UCLASS()
class TEST6_API UGameplayAbility_Fireball : public UGameplayAbility
{
	GENERATED_BODY()

public:
    UGameplayAbility_Fireball();

protected:
    virtual bool CheckCost(
        const FGameplayAbilitySpecHandle Handle,
        const FGameplayAbilityActorInfo* ActorInfo,
        FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;

    virtual void ActivateAbility(
        const FGameplayAbilitySpecHandle Handle,
        const FGameplayAbilityActorInfo* ActorInfo,
        const FGameplayAbilityActivationInfo ActivationInfo,
        const FGameplayEventData* TriggerEventData) override;


protected:
    UPROPERTY(EditDefaultsOnly, Category = "Fireball")
    TSubclassOf<AFireballProjectile> ProjectileClass;

    UPROPERTY(EditDefaultsOnly, Category = "Fireball", meta = (ClampMin = "1.0"))
    float ProjectileSpeed = 1500.f;

    float ManaCost = 10;
};
