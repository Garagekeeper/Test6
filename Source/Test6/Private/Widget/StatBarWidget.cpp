


#include "Widget/StatBarWidget.h"
#include "Widget/BarWidget.h"
#include "GAS/PlayerAttributeSet.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"

void UStatBarWidget::UpdateHealth(float CurrentVal, float MaxVal)
{
	if (HelthBar)
	{
		HelthBar->UpdateValue(CurrentVal, MaxVal);
	}
}

void UStatBarWidget::UpdateMana(float CurrentVal, float MaxVal)
{
	if (ManaBar)
	{
		ManaBar->UpdateValue(CurrentVal, MaxVal);
	}
}

void UStatBarWidget::UpdateHealth(const FOnAttributeChangeData& InData)
{

	// 최대 체력은 뽑아서 사용
	float MaxHealth = 100.f;
	bool bFound = false;
	const float TempMax = ASC->GetGameplayAttributeValue(UPlayerAttributeSet::GetMaxHealthAttribute(), bFound);
	if (bFound) MaxHealth = TempMax;

	UpdateHealth(InData.NewValue, MaxHealth);

}

void UStatBarWidget::UpdateMana(const FOnAttributeChangeData& InData)
{

	// 최대 마나는 뽑아서 사용
	float MaxMana = 100.f;
	bool bFound = false;
	const float TempMax = ASC->GetGameplayAttributeValue(UPlayerAttributeSet::GetMaxManaAttribute(), bFound);
	if (bFound) MaxMana = TempMax;

	UpdateMana(InData.NewValue, MaxMana);
}

void UStatBarWidget::UpdateMaxHealth(const FOnAttributeChangeData& InData)
{
	// 현재 체력은 뽑아서 사용
	float CurrenHealth = .0f;
	bool bFound = false;
	const float TempCurrent = ASC->GetGameplayAttributeValue(UPlayerAttributeSet::GetHealthAttribute(), bFound);
	if (bFound) CurrenHealth = TempCurrent;

	UpdateHealth(CurrenHealth, InData.NewValue);
}

void UStatBarWidget::UpdateMaxMana(const FOnAttributeChangeData& InData)
{
	// 현재 마나는 뽑아서 사용
	float CurrentMana = .0f;
	bool bFound = false;
	const float TempCurrent = ASC->GetGameplayAttributeValue(UPlayerAttributeSet::GetManaAttribute(), bFound);
	if (bFound) CurrentMana = TempCurrent;

	UpdateMana(CurrentMana, InData.NewValue);
}

void UStatBarWidget::NativeDestruct()
{
	UnbindASC();
	Super::NativeDestruct();
}

void UStatBarWidget::UnbindASC()
{
	UAbilitySystemComponent* CurrASC = ASC.Get();
	if (!CurrASC) return;

	// 델리게이트 해제
	CurrASC->GetGameplayAttributeValueChangeDelegate(UPlayerAttributeSet::GetHealthAttribute()).RemoveAll(this);
	CurrASC->GetGameplayAttributeValueChangeDelegate(UPlayerAttributeSet::GetMaxHealthAttribute()).RemoveAll(this);
	CurrASC->GetGameplayAttributeValueChangeDelegate(UPlayerAttributeSet::GetManaAttribute()).RemoveAll(this);
	CurrASC->GetGameplayAttributeValueChangeDelegate(UPlayerAttributeSet::GetMaxManaAttribute()).RemoveAll(this);

	// ASC nullptr로 밀어주기
	ASC.Reset();
}

void UStatBarWidget::InitWidget(APawn* InPawn)
{
	if (!InPawn) return;

	// 어떤 경로에서 이미 ASC가 설정 되었다면
	if (ASC.IsValid())
	{
		UnbindASC();
	}

	IAbilitySystemInterface* ASI = Cast<IAbilitySystemInterface>(InPawn);
	if (!ASI) return;

	UAbilitySystemComponent* AbilitySystemComp = ASI->GetAbilitySystemComponent();
	if (!AbilitySystemComp) return;
	ASC = AbilitySystemComp;

	// 어트리뷰트 델리게이트에 바인딩
	FOnGameplayAttributeValueChange& HealthChange = ASC->GetGameplayAttributeValueChangeDelegate(UPlayerAttributeSet::GetHealthAttribute());
	HealthChange.AddUObject(this, &UStatBarWidget::UpdateHealth);

	FOnGameplayAttributeValueChange& MaxHealthChange = ASC->GetGameplayAttributeValueChangeDelegate(UPlayerAttributeSet::GetMaxHealthAttribute());
	MaxHealthChange.AddUObject(this, &UStatBarWidget::UpdateMaxHealth);

	FOnGameplayAttributeValueChange& ManaChange = ASC->GetGameplayAttributeValueChangeDelegate(UPlayerAttributeSet::GetManaAttribute());
	ManaChange.AddUObject(this, &UStatBarWidget::UpdateMana);

	FOnGameplayAttributeValueChange& MaxManaChange = ASC->GetGameplayAttributeValueChangeDelegate(UPlayerAttributeSet::GetMaxManaAttribute());
	MaxManaChange.AddUObject(this, &UStatBarWidget::UpdateMaxMana);


	// UI 초기값 세팅
	// 체력 세팅
	bool bFound = false;
	const float HealthTempCurrent = ASC->GetGameplayAttributeValue(UPlayerAttributeSet::GetHealthAttribute(), bFound);
	float CurrentHealth = bFound ? HealthTempCurrent : 0.0f;	// 못찾았으면 0

	bFound = false;
	const float HealthTempMax = ASC->GetGameplayAttributeValue(UPlayerAttributeSet::GetMaxHealthAttribute(), bFound);
	float MaxHealth = bFound ? HealthTempMax : 100.0f;	// 못찾았으면 100


	// 마나 세팅
	bFound = false;
	const float ManaTempCurrent = ASC->GetGameplayAttributeValue(UPlayerAttributeSet::GetManaAttribute(), bFound);
	float CurrentMana = bFound ? ManaTempCurrent : 0.0f;	// 못찾았으면 0

	bFound = false;
	const float ManaTempMax = ASC->GetGameplayAttributeValue(UPlayerAttributeSet::GetMaxManaAttribute(), bFound);
	float MaxMana = bFound ? ManaTempMax : 100.0f;	// 못찾았으면 100

	UpdateHealth(CurrentHealth, MaxHealth);
	UpdateMana(CurrentMana, MaxMana);
}
