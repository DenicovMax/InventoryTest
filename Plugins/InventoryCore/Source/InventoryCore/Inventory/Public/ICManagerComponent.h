
#pragma once

#include "CoreMinimal.h"
#include "ICData.h"
#include "Components/ActorComponent.h"
#include "ICManagerComponent.generated.h"

class UICEquipWidget;
class UICComponent;
class UICWidget;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class INVENTORYCORE_API UICManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UICManagerComponent();

	void Init(UICComponent* InInventoryComponent);

	void InitEquip(UICComponent* InInventoryComponent);

	//const FInventoryCoreDataInfo* GetItemInventoryData(const FName& InID);

protected:

	UPROPERTY(EditAnywhere)
	UDataTable* ItemsData;

	UPROPERTY(EditAnywhere)
	int32 MinInventorySize = 20;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UICWidget> InventoryWidgetClass;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UICEquipWidget> EquipWidgetClass;

	UPROPERTY()
	UICCellWidget* Cell;

	UPROPERTY()
	UICWidget* InventoryWidget;

	UPROPERTY()
	UICEquipWidget* EquipWidget;

public:

	UICWidget* GetInventoryWidget() { return InventoryWidget; }
		
	UICEquipWidget* GetEquipWidget() { return EquipWidget; }

	void OnItemDropFunc(UICCellWidget* From, UICCellWidget* To);
	bool CheckEquipSlot(UICCellWidget* To, const FInventoryCoreDataInfo ToItem);
	bool CheckEquipItem(UICCellWidget* To, const FInventoryCoreDataInfo ToItem);

	void UseItem(UICCellWidget* Item);
};
