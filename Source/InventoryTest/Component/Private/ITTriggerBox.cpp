// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryTest/Component/Public/ITTriggerBox.h"
#include "Components/BoxComponent.h"
#include "InventoryTest/Interfaces/ITDamageTaker.h"
#include "InventoryTest/Character/Public/ITCharacter.h"

AITTriggerBox::AITTriggerBox()
{
	TriggerCollision = CreateDefaultSubobject<UBoxComponent>("Trigger Collision");
	SetRootComponent(TriggerCollision);
}

void AITTriggerBox::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	ApplyDamage(OtherActor);
}

void AITTriggerBox::ApplyDamage(AActor* Target)
{
	if(IITDamageTaker* DamageTaker = Cast<IITDamageTaker>(Target))
	{
		FInventoryDamageData DamageData;
		DamageData.Damage = Damage;
		DamageData.Instigator = this;

		DamageTaker->TakeDamage(DamageData);
	}
}


