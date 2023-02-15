// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryTriggerBox.generated.h"

class AInventoryCharacter;
class UBoxComponent;
/**
 * 
 */
UCLASS()
class INVENTORYTEST_API AInventoryTriggerBox : public AActor
{
	GENERATED_BODY()

	AInventoryTriggerBox();

protected:

	UPROPERTY(EditAnywhere)
	UBoxComponent* TriggerCollision;

	UPROPERTY(EditAnywhere)
	float Damage = 50.f;

public:

	void ApplyDamage(AActor* Target);

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
};
