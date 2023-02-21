
#include "InventoryTest/HUD/Public/ITHUD.h"
#include "Blueprint/UserWidget.h"

AITHUD::AITHUD()
{
	
}

UUserWidget* AITHUD::ShowWidget(const EWidgetID WidgetID, const int32 ZOrder)
{
	TSubclassOf<UUserWidget>* Class = WidgetClasses.Find(WidgetID);

	if(Class && *Class)
	{
		CreateWidgetByClass(*Class, ZOrder);
	}

	return CurrentWidget;
}

void AITHUD::HideWidget()
{
	if(CurrentWidget)
	{
		CurrentWidget->RemoveFromParent();
		CurrentWidget->SetVisibility(ESlateVisibility::Collapsed);
		CurrentWidget = nullptr;
	}
}

UUserWidget* AITHUD::CreateWidgetByClass(const TSubclassOf<UUserWidget> WidgetClass, const int32 ZOrder)
{
	CurrentWidget = CreateWidget(GetWorld(), WidgetClass);
	CurrentWidget->AddToViewport();
	CurrentWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	return CurrentWidget;
}
