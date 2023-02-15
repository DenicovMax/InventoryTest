

#include "InventoryCore/InventoryWidget/Public/InventoryCoreEquipWidget.h"

void UInventoryCoreEquipWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if(HeadCell)
	{
		HeadCell->IndexInInventory = 1;
		HeadCell->ParentInventoryWidget = this;
		HeadCell->OnItemDrop.AddUObject(this, &UInventoryCoreWidget::OnItemDropFunc);
	}
	if(BodyCell)
	{
		BodyCell->IndexInInventory = 2;
		BodyCell->ParentInventoryWidget = this;
		BodyCell->OnItemDrop.AddUObject(this, &UInventoryCoreWidget::OnItemDropFunc);
	}
	if(LeftHandCell)
	{
		LeftHandCell->IndexInInventory = 3;
		LeftHandCell->ParentInventoryWidget = this;
		LeftHandCell->OnItemDrop.AddUObject(this, &UInventoryCoreWidget::OnItemDropFunc);
	}
	if(RightHandCell)
	{
		RightHandCell->IndexInInventory = 4;
		RightHandCell->ParentInventoryWidget = this;
		RightHandCell->OnItemDrop.AddUObject(this, &UInventoryCoreWidget::OnItemDropFunc);
	}
	if(LeftFootCell)
	{
		LeftFootCell->IndexInInventory = 5;
		LeftFootCell->ParentInventoryWidget = this;
		LeftFootCell->OnItemDrop.AddUObject(this, &UInventoryCoreWidget::OnItemDropFunc);
	}
	if(RightFootCell)
	{
		RightFootCell->IndexInInventory = 6;
		RightFootCell->ParentInventoryWidget = this;
		RightFootCell->OnItemDrop.AddUObject(this, &UInventoryCoreWidget::OnItemDropFunc);
	}
	
}

bool UInventoryCoreEquipWidget::AddEquipItem(const FInventoryCoreDataInfo& Info, int32 SlotIndex)
{
	if(HeadCell && BodyCell && LeftHandCell && RightHandCell && LeftFootCell && RightFootCell)
	{
		UInventoryCoreCellWidget* Found = nullptr;
		UInventoryCoreCellWidget** FoundPtr = CellEquipWidgets.FindByPredicate([SlotIndex](UInventoryCoreCellWidget* Cell)
		{
			return Cell && Cell->IndexInInventory == SlotIndex;
		});

		if(FoundPtr)
		{
			Found = *FoundPtr;
		}
		else
		{
			for(UInventoryCoreCellWidget* Cell : CellEquipWidgets)
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
