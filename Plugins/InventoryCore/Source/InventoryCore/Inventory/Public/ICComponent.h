// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ICData.h"
#include "Components/ActorComponent.h"
#include "ICComponent.generated.h"



UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class INVENTORYCORE_API UICComponent : public UActorComponent
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere)
	TMap<int32, FInventoryCoreDataInfo> Items;

public:
	UICComponent();

	UPROPERTY(EditAnywhere)
	UDataTable* ItemsData;

	const FInventoryCoreDataInfo* GetItem(int32 SlotIndex) const { return Items.Find(SlotIndex); }

	void SetItem(int32 SlotIndex, const FInventoryCoreDataInfo& Item);
	const FInventoryCoreDataInfo* GetItemData(const FName& InID);

	void ClearItem(int32 SlotIndex);

	virtual int32 GetMaxItemAmount(int32 SlotIndex, const FInventoryCoreDataInfo& InItem);
	
	const TMap<int32, FInventoryCoreDataInfo>& GetItems() const { return Items; }

	int32 GetItemsNum() const { return Items.Num(); }	
};
