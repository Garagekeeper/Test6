

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FireballProjectile.generated.h"

class USphereComponent;
class UPrimitiveComponent;
class UProjectileMovementComponent;
class UGameplayEffect;

UCLASS()
class TEST6_API AFireballProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFireballProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
		FVector NormalImpulse, const FHitResult& Hit);

	void ApplyGameEffects(AActor* OtherActor);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "GAS")
	TObjectPtr<USphereComponent> Sphere;

	UPROPERTY(EditDefaultsOnly, Category = "GAS")
	TObjectPtr<UProjectileMovementComponent> Movement;

	UPROPERTY(EditAnywhere, Category = "GAS")
	TSubclassOf<UGameplayEffect> DirectDamageEffectClass;

	UPROPERTY(EditAnywhere, Category = "GAS")
	TSubclassOf<UGameplayEffect> BurnDamageEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GAS")
	float EffectLevel = 1.0f;

private:
	bool bHitted = false;
	float BaseDamage = 10.f;
	float BurnBasedDamage = 20.f;
};
