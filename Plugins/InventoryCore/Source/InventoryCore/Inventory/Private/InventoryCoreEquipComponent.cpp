// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryCore/Inventory/Public/InventoryCoreEquipComponent.h"


UInventoryCoreEquipComponent::UInventoryCoreEquipComponent()
{
	EquipSlots.Add(0, EEquipSlot::Es_Head);
	EquipSlots.Add(1, EEquipSlot::Es_Body);
	EquipSlots.Add(2, EEquipSlot::Es_RightHand);
	EquipSlots.Add(3, EEquipSlot::Es_LeftHand);
	EquipSlots.Add(4, EEquipSlot::Es_RightFoot);
	EquipSlots.Add(5, EEquipSlot::Es_LeftFoot);
}

int32 UInventoryCoreEquipComponent::GetMaxItemAmount(int32 SlotIndex, const FInventoryCoreDataInfo& InItem)
{
	if (InItem.Type == EItemType::It_Equip)
	{
		return 1;
	}
	return 0;
}
