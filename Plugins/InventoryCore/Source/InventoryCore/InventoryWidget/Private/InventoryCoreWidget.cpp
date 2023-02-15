
#include "InventoryCore/InventoryWidget/Public/InventoryCoreWidget.h"
#include "InventoryCore/InventoryWidget/Public/InventoryCoreCellWidget.h"
#include "Components/UniformGridPanel.h"


void UInventoryCoreWidget::NativeConstruct()
{
	Super::NativeConstruct();

	for(UInventoryCoreCellWidget* Cell : CellWidgets)
	{
		InitCell(Cell);
	}

	/*if(EquipButton)
	{
		EquipButton->OnPressed.AddDynamic(this, )
	}*/
	
}

void UInventoryCoreWidget::Init(int32 ItemsCount)
{
	if(CellsPanel)
	{
		CellsPanel->ClearChildren();
		for(int32 i = 0; i < ItemsCount; i++)
		{
			if(UInventoryCoreCellWidget* Cell = CreateCell())
			{
				Cell->IndexInInventory = i;
				CellsPanel->AddChildToUniformGrid(Cell, i / ItemsInRaw, i % ItemsInRaw);
			}
		}
	}
}

bool UInventoryCoreWidget::AddItem(const FInventoryCoreDataInfo& Info, int32 SlotIndex)
{
	if(Info.Type == EItemType::It_Currency)
	{
		if(GoldCell)
		{
			return GoldCell->AddItem(Info);	
		}
	}

	if(CellsPanel)
	{
		UInventoryCoreCellWidget* Found = nullptr;
		UInventoryCoreCellWidget** FoundPtr = CellWidgets.FindByPredicate([SlotIndex](UInventoryCoreCellWidget*	Cell)
		{
			return Cell && Cell->IndexInInventory == SlotIndex;
		});

		if(FoundPtr)
		{
			Found = *FoundPtr;
		}
		else
		{
			for(UInventoryCoreCellWidget* Cell : CellWidgets)
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


UInventoryCoreCellWidget* UInventoryCoreWidget::CreateCell()
{
	if(CellWidgetClass)
	{
		UInventoryCoreCellWidget* Cell = CreateWidget<UInventoryCoreCellWidget>(this, CellWidgetClass);
		CellWidgets.Add(Cell);

		//InitCell(Cell);
		
		return Cell;
	}
	return nullptr;
}

void UInventoryCoreWidget::InitCell(UInventoryCoreCellWidget* NewCell)
{
	if(NewCell)
	{
		NewCell->OnItemDrop.AddUObject(this, &UInventoryCoreWidget::OnItemDropFunc);
		NewCell->ParentInventoryWidget = this; 
	}
}

void UInventoryCoreWidget::OnItemDropFunc(UInventoryCoreCellWidget* From, UInventoryCoreCellWidget* To)
{
	GEngine->AddOnScreenDebugMessage(-1,10.f,FColor::Green,
		FString::Printf(TEXT("from %s to %s"),*From->GetName(),*To->GetName() ));
	OnItemDrop.Broadcast(From, To);
}

/*void UInventoryCoreWidget::OnEquipButtonPressed()
{
	FInventoryCoreDataInfo Items = ParentInventory->GetItems();
}

void UInventoryCoreWidget::OnConsumableButtonPressed()
{
	
}

void UInventoryCoreWidget::OnShowAllButtonPressed()
{
	
}*/
