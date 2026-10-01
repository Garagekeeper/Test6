


#include "Framework/Test6HUD.h"
#include "Widget/HUDWidget.h"
#include "Blueprint/UserWidget.h"

void ATest6HUD::InitHUD()
{
	if (!HUDWidgetClass) return;
	APlayerController* PC = GetOwningPlayerController();
	if (!PC) return;

	if (!HUDWidget)
	{
		HUDWidget = CreateWidget<UHUDWidget>(PC, HUDWidgetClass);
		if (HUDWidget)
		{
			HUDWidget->AddToViewport();
		}
	}
}

void ATest6HUD::BindStat(APawn* InPawn)
{
	HUDWidget->InitWidget(InPawn);
}

void ATest6HUD::BeginPlay()
{
	Super::BeginPlay();

	InitHUD();

}
