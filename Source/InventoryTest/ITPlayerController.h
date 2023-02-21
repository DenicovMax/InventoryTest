// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ITPlayerController.generated.h"


/**
 * 
 */
UCLASS()
class INVENTORYTEST_API AITPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AITPlayerController();
	
	virtual void SetupInputComponent() override;
};
