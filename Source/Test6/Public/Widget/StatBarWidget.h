

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameplayEffectTypes.h"
#include "StatBarWidget.generated.h"

class UBarWidget;
class UAbilitySystemComponent;

/**
 * 
 */
UCLASS()
class TEST6_API UStatBarWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// 체력바 업데이트 함수
	UFUNCTION(BlueprintCallable, Category = "Stats")
	void UpdateHealth(float CurrentVal, float MaxVal);

	// Mana바 업데이트 함수
	UFUNCTION(BlueprintCallable, Category = "Stats")
	void UpdateMana(float CurrentVal, float MaxVal);

	// 위젯 초기화 함수 (바인딩, 초기 값 세팅)
	void InitWidget(APawn* InPawn);

protected:
	// 델리게이트 바인딩용 함수들
	void UpdateHealth(const FOnAttributeChangeData& InData);
	void UpdateMana(const FOnAttributeChangeData& InData);
	void UpdateMaxHealth(const FOnAttributeChangeData& InData);
	void UpdateMaxMana(const FOnAttributeChangeData& InData);

	virtual void NativeDestruct() override;


private:
	void UnbindASC();


protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UBarWidget> HelthBar;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UBarWidget> ManaBar;

	UPROPERTY(BlueprintReadOnly)
	TWeakObjectPtr<UAbilitySystemComponent> ASC;
	
};
