
#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "QSObjective.generated.h"


UENUM()
enum class EObjectiveType : uint8
{
	Ot_Location,
	Ot_Interact,
	Ot_Collect
};

DECLARE_MULTICAST_DELEGATE_OneParam(FOnObjectiveCompleted, UQSObjective* /*i dnt knw*/)

UCLASS(Abstract)
class QUESTSYSTEM_API UQSObjective : public UObject
{
	GENERATED_BODY()

public:
	virtual void ActivateObjective(AActor* Instigator) {};

	UPROPERTY(EditAnywhere)
	FText Description;

	UPROPERTY(EditAnywhere)
	EObjectiveType Type;

	FOnObjectiveCompleted OnObjectiveCompleted;

	UPROPERTY(VisibleAnywhere)
	bool bIsCompleted;

	UPROPERTY(VisibleAnywhere)
	bool bCanBeCompleted;
};

UCLASS()

class QUESTSYSTEM_API UQSInteractionObjective : public UQSObjective
{
	GENERATED_BODY()

public:
	UQSInteractionObjective();

	virtual void ActivateObjective(AActor* Instigator) override;

	UPROPERTY(EditAnywhere, meta = (AllowedClasses = "QSInteractableObject"))
	AActor* Target;
};


UCLASS()
class UQSLocationObjective : public UQSObjective
{
	GENERATED_BODY()

public:
	UQSLocationObjective();

	virtual void ActivateObjective(AActor* Instigator) override;

	UPROPERTY(EditAnywhere, meta = (AllowedClasses = "QSLocationMarker"))
	AActor* Target;
};
