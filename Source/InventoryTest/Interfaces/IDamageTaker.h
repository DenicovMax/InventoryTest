
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IDamageTaker.generated.h"

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
class UIDamageTaker : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class INVENTORYTEST_API IIDamageTaker
{
	GENERATED_BODY()
public:
	virtual void TakeDamage(const FInventoryDamageData& DamageData) = 0;
};
