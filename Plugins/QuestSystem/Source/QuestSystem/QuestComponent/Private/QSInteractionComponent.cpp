
#include "QuestSystem/QuestComponent/Public/QSInteractionComponent.h"

#include "Blueprint/UserWidget.h"
#include "QuestSystem/QuestInterface/QSInteractbleObject.h"


UQSInteractionComponent::UQSInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UQSInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	OnComponentBeginOverlap.AddDynamic(this, &UQSInteractionComponent::OnComponentBeginOverlapFunc);
	OnComponentEndOverlap.AddDynamic(this, &UQSInteractionComponent::OnComponentEndOverlapFunc);
}


void UQSInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                            FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UQSInteractionComponent::OnComponentBeginOverlapFunc(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool FromSweep, const FHitResult& SweepResult)
{
	if(!OtherActor->Implements<UQSInteractbleObject>())
	{
		return;
	}

	ActorToInteract = OtherActor;

	if(InteractMessage == nullptr && InteractMessageWidget)
	{
		InteractMessage = CreateWidget(GetWorld(), InteractMessageWidget);
	}

	if(InteractMessage && !InteractMessage->IsInViewport())
	{
		InteractMessage->AddToViewport();
	}
}

void UQSInteractionComponent::OnComponentEndOverlapFunc(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(ActorToInteract == OtherActor)
	{
		ActorToInteract = nullptr;

		if(InteractMessage)
		{
			InteractMessage->RemoveFromParent();
		}
	}
}

void UQSInteractionComponent::Interact()
{
	if(ActorToInteract)
	{
		IQSInteractbleObject::Execute_Interact(ActorToInteract, GetOwner());
	}
}

