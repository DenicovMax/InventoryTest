
#pragma once

#include "CoreMinimal.h"
#include "InventoryCoreData.h"
#include "Components/ActorComponent.h"
#include "InventoryCoreManagerComponent.generated.h"

class UInventoryCoreEquipWidget;
class UInventoryCoreComponent;
class UInventoryCoreWidget;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class INVENTORYCORE_API UInventoryCoreManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UInventoryCoreManagerComponent();

	void Init(UInventoryCoreComponent* InInventoryComponent);

	void InitEquip(UInventoryCoreComponent* InInventoryComponent);

	//const FInventoryCoreDataInfo* GetItemInventoryData(const FName& InID);

protected:

	UPROPERTY(EditAnywhere)
	UDataTable* ItemsData;

	UPROPERTY(EditAnywhere)
	int32 MinInventorySize = 20;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UInventoryCoreWidget> InventoryWidgetClass;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UInventoryCoreEquipWidget> EquipWidgetClass;

	UPROPERTY()
	UInventoryCoreCellWidget* Cell;

	UPROPERTY()
	UInventoryCoreWidget* InventoryWidget;

	UPROPERTY()
	UInventoryCoreEquipWidget* EquipWidget;

public:

	UInventoryCoreWidget* GetInventoryWidget() { return InventoryWidget; }
		
	UInventoryCoreEquipWidget* GetEquipWidget() { return EquipWidget; }

	void OnItemDropFunc(UInventoryCoreCellWidget* From, UInventoryCoreCellWidget* To);
	bool CheckEquipSlot(UInventoryCoreCellWidget* To, const FInventoryCoreDataInfo ToItem);
	bool CheckEquipItem(UInventoryCoreCellWidget* To, const FInventoryCoreDataInfo ToItem);

	void UseItem(UInventoryCoreCellWidget* Item);
};
