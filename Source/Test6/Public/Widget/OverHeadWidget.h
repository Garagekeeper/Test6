

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameplayEffectTypes.h"
#include "OverHeadWidget.generated.h"

class UBarWidget;
class UAbilitySystemComponent;

/**
 * 
 */
UCLASS()
class TEST6_API UOverHeadWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void InitWidget(APawn* InPawn);

	UFUNCTION(BlueprintCallable, Category = "Stats")
	void UpdateHealth(float CurrentVal, float MaxVal);

protected:
	virtual void NativeDestruct() override;

	// 델리게이트 바인딩용 함수
	void UpdateHealth(const FOnAttributeChangeData& InData);
	void UpdateMaxHealth(const FOnAttributeChangeData& InData);


private:
	// ASC 정리 함수
	void UnbindASC();

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UBarWidget> HealthBar;

	UPROPERTY(BlueprintReadOnly)
	TWeakObjectPtr<UAbilitySystemComponent> ASC;
};
