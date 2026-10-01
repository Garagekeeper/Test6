


#include "Widget/HUDWidget.h"
#include "Widget/StatBarWidget.h"

void UHUDWidget::InitWidget(APawn* InPawn)
{
	if (StatBarWidget)
	{
		StatBarWidget->InitWidget(InPawn);
	}
}
