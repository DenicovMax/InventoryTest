// Copyright Epic Games, Inc. All Rights Reserved.

#include "ITGameMode.h"
#include "InventoryTest/Character/Public/ITCharacter.h"
#include "UObject/ConstructorHelpers.h"

AITGameMode::AITGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
