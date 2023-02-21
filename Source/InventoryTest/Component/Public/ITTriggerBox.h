// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ITTriggerBox.generated.h"

class AITCharacter;
class UBoxComponent;
/**
 * 
 */
UCLASS()
class INVENTORYTEST_API AITTriggerBox : public AActor
{
	GENERATED_BODY()

	AITTriggerBox();

protected:

	UPROPERTY(EditAnywhere)
	UBoxComponent* TriggerCollision;

	UPROPERTY(EditAnywhere)
	float Damage = 50.f;

public:

	void ApplyDamage(AActor* Target);

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
};
