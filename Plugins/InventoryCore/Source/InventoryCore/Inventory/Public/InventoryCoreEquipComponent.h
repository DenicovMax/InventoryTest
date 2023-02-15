// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryCoreComponent.h"
#include "InventoryCoreEquipComponent.generated.h"


class UInventoryCoreEquipWidget;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class INVENTORYCORE_API UInventoryCoreEquipComponent : public UInventoryCoreComponent
{
	GENERATED_BODY()

public:

	UInventoryCoreEquipComponent();
	
	UPROPERTY(EditAnywhere)
	TMap<int32, EEquipSlot> EquipSlots;

	virtual int32 GetMaxItemAmount(int32 SlotIndex, const FInventoryCoreDataInfo& InItem) override;
};
