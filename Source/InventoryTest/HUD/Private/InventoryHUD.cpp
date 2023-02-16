
#include "InventoryTest/HUD/Public/InventoryHUD.h"
#include "Blueprint/UserWidget.h"

AInventoryHUD::AInventoryHUD()
{
	
}

UUserWidget* AInventoryHUD::ShowWidget(const EWidgetID WidgetID, const int32 ZOrder)
{
	TSubclassOf<UUserWidget>* Class = WidgetClasses.Find(WidgetID);

	if(Class && *Class)
	{
		CreateWidgetByClass(*Class, ZOrder);
	}

	return CurrentWidget;
}

void AInventoryHUD::HideWidget()
{
	if(CurrentWidget)
	{
		CurrentWidget->RemoveFromParent();
		CurrentWidget->SetVisibility(ESlateVisibility::Collapsed);
		CurrentWidget = nullptr;
	}
}

UUserWidget* AInventoryHUD::CreateWidgetByClass(const TSubclassOf<UUserWidget> WidgetClass, const int32 ZOrder)
{
	CurrentWidget = CreateWidget(GetWorld(), WidgetClass);
	CurrentWidget->AddToViewport();
	CurrentWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	return CurrentWidget;
}
