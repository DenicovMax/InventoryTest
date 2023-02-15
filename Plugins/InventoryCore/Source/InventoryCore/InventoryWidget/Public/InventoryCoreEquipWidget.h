
#pragma once

#include "CoreMinimal.h"
#include "InventoryCoreWidget.h"
#include "InventoryCoreEquipWidget.generated.h"

/**
 * 
 */
UCLASS()
class INVENTORYCORE_API UInventoryCoreEquipWidget : public UInventoryCoreWidget
{
	GENERATED_BODY()

protected:

	virtual void NativeConstruct() override;

	// Only for Equip Widget
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UInventoryCoreCellWidget* HeadCell;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UInventoryCoreCellWidget* BodyCell;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UInventoryCoreCellWidget* LeftHandCell;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UInventoryCoreCellWidget* RightHandCell;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UInventoryCoreCellWidget* LeftFootCell;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UInventoryCoreCellWidget* RightFootCell;

	UPROPERTY(BlueprintReadWrite)
	TArray<UInventoryCoreCellWidget*> CellEquipWidgets;

public:

	UInventoryCoreCellWidget* GetHeadCell() { return HeadCell; }
	UInventoryCoreCellWidget* GetBodyCell() { return BodyCell; }
	UInventoryCoreCellWidget* GetLeftHandCell() { return LeftHandCell; }
	UInventoryCoreCellWidget* GetRightHandCell() { return RightHandCell; }
	UInventoryCoreCellWidget* GetLeftFootCell() { return LeftFootCell; }
	UInventoryCoreCellWidget* GetRightFootCell() { return RightFootCell; }
	
	bool AddEquipItem(const FInventoryCoreDataInfo& Info, int32 SlotIndex);
};
