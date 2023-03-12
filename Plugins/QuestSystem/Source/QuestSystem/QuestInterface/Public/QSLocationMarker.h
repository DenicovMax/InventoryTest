
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "QSLocationMarker.generated.h"

UINTERFACE()
class UQSLocationMarker : public UInterface
{
	GENERATED_BODY()
};

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnLocationReached, AActor* /*LocationMarker*/, AActor* /*OverlappedActor*/);


class QUESTSYSTEM_API IQSLocationMarker
{
	GENERATED_BODY()

public:

	virtual void NotifyOverlapWithActor(AActor* LocationMarker, AActor* OverlappedActor)
	{
		OnLocationReached.Broadcast(LocationMarker, OverlappedActor);
	}

	FOnLocationReached OnLocationReached;
};
