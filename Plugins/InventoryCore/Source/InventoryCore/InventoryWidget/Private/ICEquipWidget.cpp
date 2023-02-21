

#include "InventoryCore/InventoryWidget/Public/ICEquipWidget.h"

void UICEquipWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if(HeadCell)
	{
		HeadCell->IndexInInventory = 1;
		HeadCell->ParentInventoryWidget = this;
		HeadCell->OnItemDrop.AddUObject(this, &UICWidget::OnItemDropFunc);
	}
	if(BodyCell)
	{
		BodyCell->IndexInInventory = 2;
		BodyCell->ParentInventoryWidget = this;
		BodyCell->OnItemDrop.AddUObject(this, &UICWidget::OnItemDropFunc);
	}
	if(LeftHandCell)
	{
		LeftHandCell->IndexInInventory = 3;
		LeftHandCell->ParentInventoryWidget = this;
		LeftHandCell->OnItemDrop.AddUObject(this, &UICWidget::OnItemDropFunc);
	}
	if(RightHandCell)
	{
		RightHandCell->IndexInInventory = 4;
		RightHandCell->ParentInventoryWidget = this;
		RightHandCell->OnItemDrop.AddUObject(this, &UICWidget::OnItemDropFunc);
	}
	if(LeftFootCell)
	{
		LeftFootCell->IndexInInventory = 5;
		LeftFootCell->ParentInventoryWidget = this;
		LeftFootCell->OnItemDrop.AddUObject(this, &UICWidget::OnItemDropFunc);
	}
	if(RightFootCell)
	{
		RightFootCell->IndexInInventory = 6;
		RightFootCell->ParentInventoryWidget = this;
		RightFootCell->OnItemDrop.AddUObject(this, &UICWidget::OnItemDropFunc);
	}
	
}

bool UICEquipWidget::AddEquipItem(const FInventoryCoreDataInfo& Info, int32 SlotIndex)
{
	if(HeadCell && BodyCell && LeftHandCell && RightHandCell && LeftFootCell && RightFootCell)
	{
		UICCellWidget* Found = nullptr;
		UICCellWidget** FoundPtr = CellEquipWidgets.FindByPredicate([SlotIndex](UICCellWidget* Cell)
		{
			return Cell && Cell->IndexInInventory == SlotIndex;
		});

		if(FoundPtr)
		{
			Found = *FoundPtr;
		}
		else
		{
			for(UICCellWidget* Cell : CellEquipWidgets)
			{
				if(!Cell->HasItem())
				{
					Found = Cell;
					break;
				}
			}
		}

		if(Found)
		{
			return Found->AddItem(Info);
		}
	}
	
	return false;
}
