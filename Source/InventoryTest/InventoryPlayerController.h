// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InventoryPlayerController.generated.h"


/**
 * 
 */
UCLASS()
class INVENTORYTEST_API AInventoryPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AInventoryPlayerController();
	
	virtual void SetupInputComponent() override;
};
