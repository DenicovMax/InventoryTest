
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "QSQuest.generated.h"


class UQSObjective;

UCLASS()
class QUESTSYSTEM_API AQSQuest : public AActor
{
	GENERATED_BODY()

public:
	AQSQuest();

protected:
	
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	FText QuestName;

	UPROPERTY(EditAnywhere)
	FText Description;

	UPROPERTY(EditAnywhere)
	TArray<UQSObjective*> Objectives;

	UPROPERTY(EditAnywhere)
	bool bIsStoryQuest = true;

	UPROPERTY(EditAnywhere)
	bool bKeepObjectivesOrder = true;

	UPROPERTY(EditAnywhere)
	AQSQuest* PreviousQuest;

	UPROPERTY(EditAnywhere)
	bool bIsTaken = false;

	UFUNCTION(BlueprintCallable, CallInEditor)
	void UpdateLocation();

	UFUNCTION()
	void TakeQuest(AActor* Character);

	void OnObjectiveCompleted(UQSObjective* Objective);

#if WITH_EDITOR

	UFUNCTION(CallInEditor)
	void AddInteractableObjective();

	UFUNCTION(CallInEditor)
	void AddLocationObjective();

#endif
};
