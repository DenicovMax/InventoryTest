
#include "QuestSystem/Actors/Public/QSQuest.h"
#include "QuestSystem/QuestComponent/Public/QSObjective.h"



AQSQuest::AQSQuest()
{
	PrimaryActorTick.bCanEverTick = true;
}


void AQSQuest::BeginPlay()
{
	Super::BeginPlay();

	AActor* ParentActor = GetAttachParentActor();
	if(ParentActor)
	{
		TakeQuest(ParentActor);
	}
}


void AQSQuest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AQSQuest::UpdateLocation()
{
	AActor* ParentActor = GetAttachParentActor();
	if(ParentActor)
	{
		SetActorLocation(ParentActor->GetActorLocation());
	}
}

void AQSQuest::TakeQuest(AActor* Character)
{
	if(bIsTaken) { return; }

	for (int32 i = 0; i < Objectives.Num(); i++)
	{
		UQSObjective* Objective = Objectives[i];
		if(Objective == nullptr)
		{
			return;
		}

		Objective->ActivateObjective(Character);
		//Objective->
	}
}

void AQSQuest::OnObjectiveCompleted(UQSObjective* Objective)
{
	
}

void AQSQuest::AddInteractableObjective()
{
	
}

void AQSQuest::AddLocationObjective()
{
	
}

