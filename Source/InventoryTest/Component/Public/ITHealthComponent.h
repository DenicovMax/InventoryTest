// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ITHealthComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class INVENTORYTEST_API UITHealthComponent : public UActorComponent
{
	GENERATED_BODY()
	
	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnHealthChangeDelegate, float /*New Health*/, float /*Old Health*/)
	DECLARE_MULTICAST_DELEGATE(FOnDieDelegate)
	
public:
	FOnHealthChangeDelegate OnHealthChangeDelegate;
	FOnDieDelegate OnDieDelegate;
	
public:
	UPROPERTY(EditAnywhere)
	float Health = 100.f;
	
	void SetHealth(float NewHealth);

	UFUNCTION(BlueprintCallable)
	float GetHealth() const;

	bool IsDeath() const;
};
