
#pragma once

#include "CoreMinimal.h"
#include "ICWidget.h"
#include "ICEquipWidget.generated.h"

/**
 * 
 */
UCLASS()
class INVENTORYCORE_API UICEquipWidget : public UICWidget
{
	GENERATED_BODY()

protected:

	virtual void NativeConstruct() override;

	// Only for Equip Widget
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UICCellWidget* HeadCell;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UICCellWidget* BodyCell;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UICCellWidget* LeftHandCell;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UICCellWidget* RightHandCell;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UICCellWidget* LeftFootCell;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UICCellWidget* RightFootCell;

	UPROPERTY(BlueprintReadWrite)
	TArray<UICCellWidget*> CellEquipWidgets;

public:

	UICCellWidget* GetHeadCell() { return HeadCell; }
	UICCellWidget* GetBodyCell() { return BodyCell; }
	UICCellWidget* GetLeftHandCell() { return LeftHandCell; }
	UICCellWidget* GetRightHandCell() { return RightHandCell; }
	UICCellWidget* GetLeftFootCell() { return LeftFootCell; }
	UICCellWidget* GetRightFootCell() { return RightFootCell; }
	
	bool AddEquipItem(const FInventoryCoreDataInfo& Info, int32 SlotIndex);
};
