
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BarWidget.generated.h"

class UTextBlock;
class UProgressBar;

/**
 * 
 */
UCLASS()
class TEST6_API UBarWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// 현재/최대 값 변경 함수
	UFUNCTION(BlueprintCallable, Category = "Stats")
	void UpdateValue(float InValue, float InMaxValue);

protected:
	virtual void NativePreConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	// 프로그래스 바 업데이트용 함수
	void UpdateBar(float InDeltaTime);
	// 텍스트 업데이트용 함수
	void UpdateText();

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> MaxValueText;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> CurrentValueText;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UProgressBar> ProgressBar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float InterpSpeed = 5.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	FLinearColor BarColor = FLinearColor::White;

private:
	float TargetValue = 1.f;
	float CurrentValue = 100.f;
	float MaxValue = 100.f;
	
};
