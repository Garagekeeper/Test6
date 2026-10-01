


#include "Character/Test6Player.h"
#include "GAS/PlayerAttributeSet.h"
#include "Framework/Test6HUD.h"
#include "AbilitySystemComponent.h"
#include "EnhancedInputComponent.h"

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

	// HUD 위젯 바인딩
	APlayerController* PC = Cast<APlayerController>(GetController());
	if (!PC) return;

	ATest6HUD* HUD = Cast<ATest6HUD>(PC->GetHUD());
	if (HUD)
		HUD->BindStat(this);

	GiveDefaultAbilites();
}

void ATest6Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		SetupAbilityInputs(EnhancedInputComponent);
	}
}

void ATest6Player::GiveDefaultAbilites()
{
	for (auto& DefaultAbility : DefaultAbilities)
	{
		// Give Ability
		FGameplayAbilitySpec Spec(DefaultAbility.AbilityClass, DefaultAbility.AbilityLevel, static_cast<int32>(DefaultAbility.InputID));
		FGameplayAbilitySpecHandle Handle = ASC->GiveAbility(Spec);
		GrantedDefaultAbilityHandles.Add(Handle);

		// 받자 마자 활성화되는 경우는 바로 실행
		if (DefaultAbility.bActivateOnGranted)
		{
			ASC->TryActivateAbility(Handle);
		}
	}
}

void ATest6Player::SetupAbilityInputs(UEnhancedInputComponent* EnhancedInputComponent)
{
	if (!EnhancedInputComponent) return;

	for (const FPlayerAbilityConfig& DefaultAbility : DefaultAbilities)
	{
		if (DefaultAbility.InputAction && DefaultAbility.InputID != EAbilityInputID::None)
		{
			EnhancedInputComponent->BindAction(
				DefaultAbility.InputAction,
				ETriggerEvent::Started,
				this,
				&ATest6Player::OnAbilityInputPressed,
				DefaultAbility.InputID
			);

			EnhancedInputComponent->BindAction(
				DefaultAbility.InputAction,
				ETriggerEvent::Completed,
				this,
				&ATest6Player::OnAbilityInputReleased,
				DefaultAbility.InputID
			);
		}
	}
}


void ATest6Player::OnAbilityInputPressed(EAbilityInputID InputID)
{
	if (ASC && InputID != EAbilityInputID::None)
	{
		ASC->AbilityLocalInputPressed(static_cast<int32>(InputID));
	}
}

void ATest6Player::OnAbilityInputReleased(EAbilityInputID InputID)
{
	if (ASC && InputID != EAbilityInputID::None)
	{
		ASC->AbilityLocalInputReleased(static_cast<int32>(InputID));
	}
}
