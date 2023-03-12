
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "QSInteractbleObject.generated.h"

UINTERFACE()
class UQSInteractbleObject : public UInterface
{
	GENERATED_BODY()
};


DECLARE_MULTICAST_DELEGATE_TwoParams(FOnInteractionFinished, AActor* /*InteractObject*/, AActor* /*InteractInstigator*/)


class QUESTSYSTEM_API IQSInteractbleObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Interact(AActor* InteractInstigator);

	UFUNCTION()
	virtual void Interact_Implementation(AActor* InteractInstigator) { };

	virtual void NotifyInteractionFinished(AActor* InteractObject, AActor* InteractInstigator)
	{
		OnInteractionFinished.Broadcast(InteractObject, InteractInstigator);
	}

	FOnInteractionFinished OnInteractionFinished;
};
