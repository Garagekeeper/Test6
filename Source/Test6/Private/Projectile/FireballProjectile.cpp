

#include "Projectile/FireballProjectile.h"
#include "Components/SphereComponent.h"
#include "AbilitySystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Character/Test6Player.h"
#include "Character/Test6Enemy.h"

// Sets default values
AFireballProjectile::AFireballProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	SetRootComponent(Sphere);

	Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
	Movement->SetUpdatedComponent(Sphere);
}

// Called when the game starts or when spawned
void AFireballProjectile::BeginPlay()
{ 
	Super::BeginPlay();
	Sphere->SetSphereRadius(16.f, true);
	Sphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Sphere->SetCollisionObjectType(ECC_WorldDynamic);
	Sphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	Sphere->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	Sphere->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);
	Sphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
	Sphere->SetNotifyRigidBodyCollision(true);
	Sphere->OnComponentHit.AddDynamic(this, &AFireballProjectile::OnHit);
	if (AActor* OwnerActor = GetOwner())
	{
		Sphere->IgnoreActorWhenMoving(OwnerActor, true);
	}
	Movement->SetUpdatedComponent(Sphere);
}

// Called every frame
void AFireballProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFireballProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (bHitted || !OtherActor || OtherActor == this || OtherActor == GetOwner()) return;
	bHitted = true;

	if (OtherActor->IsA<ATest6Enemy>())
	{
	UE_LOG(LogTemp, Display, TEXT("Fireball hit: %s"), *GetNameSafe(OtherActor));
		ApplyGameEffects(OtherActor);
	}

	Destroy();
}

void AFireballProjectile::ApplyGameEffects(AActor* OtherActor)
{
	if (!OtherActor) return;
	if (!DirectDamageEffectClass || !BurnDamageEffectClass) return;

	ATest6Character* Target = Cast<ATest6Character>(OtherActor);
	if (!Target) return;

	UAbilitySystemComponent* TargetASC = Target->GetAbilitySystemComponent();
	ATest6Character* OwnCharhacter = Cast<ATest6Character>(GetOwner());
	if (!OwnCharhacter) return;

	UAbilitySystemComponent* OwnerASC = OwnCharhacter->GetAbilitySystemComponent();


	if (!TargetASC) return;

	// 컨택스트 설정(이펙트의 정보들을 설정)
	FGameplayEffectContextHandle EffectContext = OwnerASC->MakeEffectContext();
	EffectContext.AddSourceObject(this);
	EffectContext.AddInstigator(this, this);


	// 이팩트 스팩 설정(직접타격)
	FGameplayEffectSpecHandle SpecHandle = OwnerASC->MakeOutgoingSpec(DirectDamageEffectClass, EffectLevel, EffectContext);
	if (!SpecHandle.IsValid()) return;

	// 현재 상대가 화상 상태인지 확인
	const bool bBurning = TargetASC->HasMatchingGameplayTag(
		FGameplayTag::RequestGameplayTag(TEXT("GAS.TEST6.Debuff.Burn")));

	// 화상 상태이면 SetbyCAller를 통해서 값 변경
	SpecHandle.Data->SetSetByCallerMagnitude(
		FGameplayTag::RequestGameplayTag(TEXT("GAS.Data.FireballDamage")),
		bBurning ? BurnBasedDamage : BaseDamage);

	// Owner가 Target에게 Effec적용
	FActiveGameplayEffectHandle ActiveEffectHandle = OwnerASC->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), TargetASC);


	// 이팩트 스팩 설정(화상)
	SpecHandle = OwnerASC->MakeOutgoingSpec(BurnDamageEffectClass, EffectLevel, EffectContext);
	if (!SpecHandle.IsValid()) return;
	

	// Owner가 Target에게 Effec적용
	ActiveEffectHandle = OwnerASC->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), TargetASC);

}

