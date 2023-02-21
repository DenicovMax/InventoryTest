
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ITDamageTaker.generated.h"

USTRUCT()
struct FInventoryDamageData
{
	GENERATED_BODY()
public:
	float Damage = 0.f;

	UPROPERTY()
	AActor* Instigator = nullptr;
};


UINTERFACE(MinimalAPI)
class UITDamageTaker : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class INVENTORYTEST_API IITDamageTaker
{
	GENERATED_BODY()
public:
	virtual void TakeDamage(const FInventoryDamageData& DamageData) = 0;
};
