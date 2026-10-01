


#include "Character/Test6Character.h"
#include "AbilitySystemComponent.h"

// Sets default values
ATest6Character::ATest6Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ASC = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("ASC"));

}

UAbilitySystemComponent* ATest6Character::GetAbilitySystemComponent() const
{
	return ASC;
}

// Called when the game starts or when spawned
void ATest6Character::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATest6Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATest6Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATest6Character::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (IsValid(ASC))
	{
		ASC->InitAbilityActorInfo(this, this);
	}
}

