


#include "Character/Test6Player.h"
#include "GAS/PlayerAttributeSet.h"
#include "Framework/Test6HUD.h"

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

	APlayerController* PC = Cast<APlayerController>(GetController());
	if (!PC) return;

	ATest6HUD* HUD = Cast<ATest6HUD>(PC->GetHUD());
	if (!HUD) return;
	HUD->BindStat(this);
}
