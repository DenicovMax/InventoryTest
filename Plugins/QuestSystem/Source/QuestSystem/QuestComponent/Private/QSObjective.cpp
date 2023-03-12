// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestSystem/QuestComponent/Public/QSObjective.h"

#include "QuestSystem/QuestInterface/Public/QSInteractbleObject.h"

UQSInteractionObjective::UQSInteractionObjective()
{
	Type = EObjectiveType::Ot_Interact;
}

void UQSInteractionObjective::ActivateObjective(AActor* Instigator)
{
	if(auto* InteractObject = Cast<IQSInteractbleObject>(Target))
	{
		InteractObject->OnInteractionFinished.AddLambda([this, Instigator](AActor* Object, AActor* InteractInstigator)
		{
			if(bCanBeCompleted && Instigator == InteractInstigator)
			{
				bIsCompleted = true;
				OnObjectiveCompleted.Broadcast(this);
			}
		});
	}
}

UQSLocationObjective::UQSLocationObjective()
{
	Type = EObjectiveType::Ot_Location;
}

void UQSLocationObjective::ActivateObjective(AActor* Instigator)
{
	
}
