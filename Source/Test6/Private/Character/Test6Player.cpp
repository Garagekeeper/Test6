


#include "Character/Test6Player.h"
#include "GAS/PlayerAttributeSet.h"

ATest6Player::ATest6Player()
{
	PlayerAttributeSet = CreateDefaultSubobject<UPlayerAttributeSet>(TEXT("Stat"));
}

UPlayerAttributeSet* ATest6Player::GetStatAttribute() const
{
	return PlayerAttributeSet;
}

void ATest6Player::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}
