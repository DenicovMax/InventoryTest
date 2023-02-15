
#include "InventoryCore/Inventory/Public/InventoryCoreComponent.h"

UInventoryCoreComponent::UInventoryCoreComponent()
{
	
}

void UInventoryCoreComponent::SetItem(int32 SlotIndex, const FInventoryCoreDataInfo& Item)
{
	ClearItem(SlotIndex);

	//Item.ID = GetItemData(Item.ID);

	Items.Add(SlotIndex, Item);
}

const FInventoryCoreDataInfo* UInventoryCoreComponent::GetItemData(const FName& InID)
{
	return ItemsData ? ItemsData->FindRow<FInventoryCoreDataInfo>(InID, "") : nullptr;
}

void UInventoryCoreComponent::ClearItem(int32 SlotIndex)
{
	Items.Remove(SlotIndex);
}

int32 UInventoryCoreComponent::GetMaxItemAmount(int32 SlotIndex, const FInventoryCoreDataInfo& InItem)
{
	FInventoryCoreDataInfo* Slot = Items.Find(SlotIndex);

	if(InItem.Count == 0.f)
	{
		return 0;
	}
	return -1;
}
