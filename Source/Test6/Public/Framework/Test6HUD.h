

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
	UFUNCTION(BlueprintCallable)
	void InitHUD();
	
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
