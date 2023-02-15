// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryTest/Component/Public/InventoryTriggerBox.h"
#include "Components/BoxComponent.h"
#include "InventoryTest/Interfaces/IDamageTaker.h"
#include "InventoryTest/Character/Public/InventoryCharacter.h"

AInventoryTriggerBox::AInventoryTriggerBox()
{
	TriggerCollision = CreateDefaultSubobject<UBoxComponent>("Trigger Collision");
	SetRootComponent(TriggerCollision);
}

void AInventoryTriggerBox::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	ApplyDamage(OtherActor);
}

void AInventoryTriggerBox::ApplyDamage(AActor* Target)
{
	if(IIDamageTaker* DamageTaker = Cast<IIDamageTaker>(Target))
	{
		FInventoryDamageData DamageData;
		DamageData.Damage = Damage;
		DamageData.Instigator = this;

		DamageTaker->TakeDamage(DamageData);
	}
}


