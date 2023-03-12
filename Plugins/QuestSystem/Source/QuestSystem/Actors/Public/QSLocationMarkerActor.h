
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "QuestSystem/QuestInterface/Public/QSLocationMarker.h"
#include "QSLocationMarkerActor.generated.h"

UCLASS()
class QUESTSYSTEM_API AQSLocationMarkerActor : public AActor, public IQSLocationMarker
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	void OnOverlappedByActor(AActor* OverlappingActor)
	{
		NotifyOverlapWithActor(this, OverlappingActor);
	}
};
