
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "InventoryHUD.generated.h"


UENUM()
enum class EWidgetID : uint8
{
	W_Death_Widget,
	W_HealthBar_Widget,
	W_Media_Widget
};

UCLASS()
class INVENTORYTEST_API AInventoryHUD : public AHUD
{
	GENERATED_BODY()

public:
	AInventoryHUD();

	UFUNCTION(BlueprintCallable)
	UUserWidget* ShowWidget(const EWidgetID WidgetID, const int32 ZOrder);

	UFUNCTION(BlueprintCallable)
	void HideWidget();
	
	UFUNCTION(BlueprintPure)
	UUserWidget* GetCurrentWidget() { return CurrentWidget; }

protected:

	UUserWidget* CreateWidgetByClass(const TSubclassOf<UUserWidget> WidgetClass, const int32 ZOrder = 0);

	UPROPERTY(EditAnywhere)
	TMap<EWidgetID, TSubclassOf<UUserWidget>> WidgetClasses;
	
	UPROPERTY()
	UUserWidget* CurrentWidget;
};
