

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Test6HUD.generated.h"

/**
 * 
 */
UCLASS()
class TEST6_API ATest6HUD : public AHUD
{
	GENERATED_BODY()

public:
	// HUD위젯을 생성하고 뷰포트에 띄우는 함수
	UFUNCTION(BlueprintCallable)
	void InitHUD();
	
	// 실제 Player와 위젯을 바인딩하는 함수
	UFUNCTION(BlueprintCallable)
	void BindStat(APawn* InPawn);

	UFUNCTION(BlueprintCallable)
	UHUDWidget* GetHUDWidget() const { return HUDWidget; }

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UHUDWidget> HUDWidgetClass;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UHUDWidget> HUDWidget;
	
};
