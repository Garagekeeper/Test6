


#include "GAS/EnemyAttributeSet.h"
#include "GameplayEffectExtension.h"

UEnemyAttributeSet::UEnemyAttributeSet()
{
	InitHealth(100.0f);
	InitMaxHealth(100.0f);
}

void UEnemyAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	if (Attribute == GetHealthAttribute())
	{
		// Health가 변경되려고 해서 호출되었다.
		NewValue = FMath::Clamp(NewValue, 0, GetMaxHealth());
	}
	else if (Attribute == GetMaxHealthAttribute())
	{
		// MaxHealth가 변경되려고 해서 호출되었다.
		NewValue = FMath::Max(0, NewValue);
	}
}

void UEnemyAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	// BaseValue가 변경될 때만 실행된다.
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetDamageAttribute())
	{
		// 이팩트로 인해 변경된 어트리뷰트가 Damage다
		const float LocalDamage = GetDamage();
		SetDamage(0.0f);	// [가장 중요] : 메타어트리뷰트는 사용했으면 비워야 한다.

		if (LocalDamage > 0)
		{
			float FinalDamage = LocalDamage;	// 각종 계산 추가(방어력, 최소대미지보장, 쉴드, 피해 증가 등등)
			FinalDamage = FMath::Max(1.0f, FinalDamage);			// 최소대미지 보장

			const float NewHealth = FMath::Clamp(GetHealth() - FinalDamage, 0.0f, GetMaxHealth());
			SetHealth(NewHealth);

			// 값에 따른 추가 처리
		}
	}
}
