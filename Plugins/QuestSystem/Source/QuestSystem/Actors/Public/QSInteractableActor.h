
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "QuestSystem/QuestInterface/Public/QSInteractbleObject.h"
#include "QSInteractableActor.generated.h"

UCLASS()
class QUESTSYSTEM_API AQSInteractableActor : public AActor, public IQSInteractbleObject
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	void OnInteractionFinished(AActor* InteractInstigator)
	{
		NotifyInteractionFinished(this, InteractInstigator);
	}
};
