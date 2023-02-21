
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ITPlayerHPStatus.generated.h"

class UProgressBar;

UCLASS()
class INVENTORYTEST_API UITPlayerHPStatus : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere)
	UProgressBar* HealthBar;
};
