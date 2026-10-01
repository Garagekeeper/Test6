

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "EnemyAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class TEST6_API UEnemyAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UEnemyAttributeSet();


	// CurrentValue 변경 전에 실행되는 함수
	// 값의 Clamping용도로 사용
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	// CurrentValue 변경 후에 실행되는 함수
	// 값의 변화 감지나, UI에 반영하기 위해 사용
	//virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;

	// 이펙트가 적용 된 후에 실행되는 함수
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

public:

	UPROPERTY(BlueprintReadOnly, Category = "Base Stat")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS_BASIC(UEnemyAttributeSet, Health);

	UPROPERTY(BlueprintReadOnly, Category = "Base Stat")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS_BASIC(UEnemyAttributeSet, MaxHealth);

	UPROPERTY(BlueprintReadOnly, Category = "Meta Attribute")
	FGameplayAttributeData Damage;
	ATTRIBUTE_ACCESSORS_BASIC(UEnemyAttributeSet, Damage);
	
};
