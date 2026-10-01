


#include "Character/Test6Enemy.h"
#include "GAS/EnemyAttributeSet.h"
#include "Framework/Test6HUD.h"

ATest6Enemy::ATest6Enemy()
{
	EnemyAttributeSet = CreateDefaultSubobject<UEnemyAttributeSet>(TEXT("Stat"));
}

UEnemyAttributeSet* ATest6Enemy::GetStatAttribute() const
{
	return EnemyAttributeSet;
}

void ATest6Enemy::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	APlayerController* PC = Cast<APlayerController>(GetController());
	if (!PC) return;

	ATest6HUD* HUD = Cast<ATest6HUD>(PC->GetHUD());
	if (!HUD) return;
	//HUD->BindStat();
}
