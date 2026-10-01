

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDWidget.generated.h"

class UStatBarWidget;
/**
 * 
 */
UCLASS()
class TEST6_API UHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void InitWidget(APawn* InPawn);

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UStatBarWidget> StatBarWidget;
};
