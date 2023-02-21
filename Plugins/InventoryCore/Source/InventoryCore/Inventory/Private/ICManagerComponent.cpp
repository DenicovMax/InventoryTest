
#include "InventoryCore/Inventory/Public/ICManagerComponent.h"
#include "InventoryCore/Inventory/Public/ICComponent.h"
#include "Blueprint/UserWidget.h"
#include "InventoryCore/InventoryWidget/Public/ICWidget.h"
#include "InventoryCore/InventoryWidget/Public/ICEquipWidget.h"


UICManagerComponent::UICManagerComponent()
{
	
}

void UICManagerComponent::Init(UICComponent* InInventoryComponent)
{
	if(InventoryWidgetClass)
	{
		InventoryWidget = CreateWidget<UICWidget>(GetWorld(), InventoryWidgetClass);
		InventoryWidget->ParentInventory = InInventoryComponent;
		
		TArray<FInventoryCoreDataInfo*> ItemsArray;
		InventoryWidget->ParentInventory->ItemsData->GetAllRows<FInventoryCoreDataInfo>(TEXT("ItemsArray"), ItemsArray);

		InventoryWidget->Init(FMath::Max(MinInventorySize, ItemsArray.Num()));
		InventoryWidget->OnItemDrop.AddUObject(this, &ThisClass::OnItemDropFunc);
		
		for(int32 i = 0; i < ItemsArray.Num(); i++)
		{
			if(const FInventoryCoreDataInfo* Data = ItemsArray[i])
			{
				if(Data->Count > 0)
				{
					InventoryWidget->AddItem(*Data, i);
				}
			}
		}
	}
}

void UICManagerComponent::InitEquip(UICComponent* InInventoryComponent)
{
	if(InInventoryComponent && EquipWidgetClass)
	{
		EquipWidget = CreateWidget<UICEquipWidget>(GetWorld(), EquipWidgetClass);
		EquipWidget->ParentInventory = InInventoryComponent;
		EquipWidget->OnItemDrop.AddUObject(this, &ThisClass::OnItemDropFunc);

		/*TArray<FInventoryCoreDataInfo*> ItemsArray;
		EquipWidget->ParentInventory->ItemsData->GetAllRows<FInventoryCoreDataInfo>(TEXT("ItemsArray"), ItemsArray);
		
		for(int32 i = 0; i < ItemsArray.Num(); i++)
		{
			if(const FInventoryCoreDataInfo* Data = ItemsArray[i])
			{
				if(Data->Count > 0)
				{
					EquipWidget->AddEquipItem(*Data, i);
				}
			}
		}*/
		
		EquipWidget->AddToViewport();
		EquipWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

/*const FInventoryCoreDataInfo* UICManagerComponent::GetItemInventoryData(const FName& InID)
{
	return InventoryWidget->ParentInventory->ItemsData ? InventoryWidget->ParentInventory->ItemsData->FindRow<FInventoryCoreDataInfo>(InID, "") : nullptr;
}*/

void UICManagerComponent::OnItemDropFunc(UICCellWidget* From, UICCellWidget* To)
{
	if(From == nullptr || To == nullptr)
	{
		return;
	}

	UICComponent* FromInventory = From->GetParentInventory();
	UICComponent* ToInventory = To->GetParentInventory();

	if(FromInventory == nullptr || ToInventory == nullptr)
	{
		return;
	}

	const FInventoryCoreDataInfo FromItem = From->GetItem();
	if(FromItem.Count == 0)
	{
		return;
	}
	const FInventoryCoreDataInfo ToItem = To->GetItem();

	const FInventoryCoreDataInfo FromInfo = FromItem;
	const FInventoryCoreDataInfo ToInfo = ToItem;
	
	const int32 FromItemAmount = FromInventory->GetMaxItemAmount(From->IndexInInventory, FromInfo);
	const int32 ToItemAmount = ToInventory->GetMaxItemAmount(To->IndexInInventory, FromInfo);
	
	if(FromItemAmount == 0 || ToItemAmount == 0)
	{
		return;
	}
	
	FInventoryCoreDataInfo NewFromItem = ToItem;
	FInventoryCoreDataInfo NewToItem = FromItem;
	

	if(ToItemAmount > 0)
	{
		if(FromItem.Count <= NewToItem.Count)
		{
			NewFromItem.ID = NewToItem.ID;
			NewFromItem.Count = FromItem.Count - NewToItem.Count;
		}
	}
	NewToItem.Count = FMath::Max(ToItemAmount, FromItem.Count);

	if(ToInventory == EquipWidget->ParentInventory)
	{
		if(CheckEquipItem(To, FromItem) == false)
		{
			return;
		}

		if(ToItem.ID == NAME_None)
		{
			NewFromItem = NewToItem;
			NewFromItem.Count = NewFromItem.Count - 1;
			NewToItem.Count = 1.f;
		}
		else
		{
			return;
		}
	}
	else
	{
		if(NewFromItem.ID == NewToItem.ID)
		{
			NewToItem.Count = NewToItem.Count + NewFromItem.Count;
			NewFromItem.ID =  NAME_None;
		}
	}

	/*if(ToInventory == EquipWidget->ParentInventory && CheckEquipItem(To, ToItem) == true)
	{
		From->Clear();
		From->AddItem(NewFromItem);
		if(NewFromItem.ID == NAME_None)
		{
			From ->Clear();
		}

		To->Clear();
		To->AddItem(NewToItem);

		FromInventory->SetItem(From->IndexInInventory, NewFromItem);
		ToInventory->SetItem(To->IndexInInventory, NewToItem);
	}
	else
	{*/
	
	From->Clear();
	From->AddItem(NewFromItem);
	if(NewFromItem.ID == NAME_None)
	{
		From ->Clear();
	}

	To->Clear();
	To->AddItem(NewToItem);

	FromInventory->SetItem(From->IndexInInventory, NewFromItem);
	ToInventory->SetItem(To->IndexInInventory, NewToItem);
	
	
	//const FInventoryCoreDataInfo* NewFromInfo = NewFromItem.Count > 0 ? GetItemInventoryData(NewFromItem.ID) : nullptr;
	//const FInventoryCoreDataInfo* NewToInfo = GetItemInventoryData(NewToItem.ID);
}

bool UICManagerComponent::CheckEquipItem(UICCellWidget* To,
												const FInventoryCoreDataInfo FromItem)
{
	if(CheckEquipSlot(To, FromItem))
	{
		return true;
	}
	return false;
}

bool UICManagerComponent::CheckEquipSlot(UICCellWidget* To,
                                                const FInventoryCoreDataInfo FromItem)
{
	if(EquipWidget->GetHeadCell() == To && FromItem.EquipSlot == EEquipSlot::Es_Head)
	{
		return true;
	}
	if(EquipWidget->GetBodyCell() == To && FromItem.EquipSlot == EEquipSlot::Es_Body)
	{
		return true;
	}
	if(EquipWidget->GetLeftHandCell() == To && FromItem.EquipSlot == EEquipSlot::Es_LeftHand)
	{
		return true;
	}
	if(EquipWidget->GetRightHandCell() == To && FromItem.EquipSlot == EEquipSlot::Es_RightHand)
	{
		return true;
	}
	if(EquipWidget->GetLeftFootCell() == To && FromItem.EquipSlot == EEquipSlot::Es_LeftFoot)
	{
		return true;
	}
	if(EquipWidget->GetRightFootCell() == To && FromItem.EquipSlot == EEquipSlot::Es_RightFoot)
	{
		return true;
	}
	return false;
}



