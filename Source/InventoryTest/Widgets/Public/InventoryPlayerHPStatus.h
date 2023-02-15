
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryPlayerHPStatus.generated.h"

class UProgressBar;

UCLASS()
class INVENTORYTEST_API UInventoryPlayerHPStatus : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere)
	UProgressBar* HealthBar;
};
