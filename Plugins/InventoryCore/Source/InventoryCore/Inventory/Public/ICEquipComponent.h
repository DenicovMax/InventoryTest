// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ICComponent.h"
#include "ICEquipComponent.generated.h"


class UICEquipWidget;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class INVENTORYCORE_API UICEquipComponent : public UICComponent
{
	GENERATED_BODY()

public:

	UICEquipComponent();
	
	UPROPERTY(EditAnywhere)
	TMap<int32, EEquipSlot> EquipSlots;

	virtual int32 GetMaxItemAmount(int32 SlotIndex, const FInventoryCoreDataInfo& InItem) override;
};
