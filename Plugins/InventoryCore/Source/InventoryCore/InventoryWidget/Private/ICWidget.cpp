
#include "InventoryCore/InventoryWidget/Public/ICWidget.h"
#include "InventoryCore/InventoryWidget/Public/ICCellWidget.h"
#include "Components/UniformGridPanel.h"


void UICWidget::NativeConstruct()
{
	Super::NativeConstruct();

	for(UICCellWidget* Cell : CellWidgets)
	{
		InitCell(Cell);
	}

	/*if(EquipButton)
	{
		EquipButton->OnPressed.AddDynamic(this, )
	}*/
	
}

void UICWidget::Init(int32 ItemsCount)
{
	if(CellsPanel)
	{
		CellsPanel->ClearChildren();
		for(int32 i = 0; i < ItemsCount; i++)
		{
			if(UICCellWidget* Cell = CreateCell())
			{
				Cell->IndexInInventory = i;
				CellsPanel->AddChildToUniformGrid(Cell, i / ItemsInRaw, i % ItemsInRaw);
			}
		}
	}
}

bool UICWidget::AddItem(const FInventoryCoreDataInfo& Info, int32 SlotIndex)
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
		UICCellWidget* Found = nullptr;
		UICCellWidget** FoundPtr = CellWidgets.FindByPredicate([SlotIndex](UICCellWidget*	Cell)
		{
			return Cell && Cell->IndexInInventory == SlotIndex;
		});

		if(FoundPtr)
		{
			Found = *FoundPtr;
		}
		else
		{
			for(UICCellWidget* Cell : CellWidgets)
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


UICCellWidget* UICWidget::CreateCell()
{
	if(CellWidgetClass)
	{
		UICCellWidget* Cell = CreateWidget<UICCellWidget>(this, CellWidgetClass);
		CellWidgets.Add(Cell);

		//InitCell(Cell);
		
		return Cell;
	}
	return nullptr;
}

void UICWidget::InitCell(UICCellWidget* NewCell)
{
	if(NewCell)
	{
		NewCell->OnItemDrop.AddUObject(this, &UICWidget::OnItemDropFunc);
		NewCell->ParentInventoryWidget = this; 
	}
}

void UICWidget::OnItemDropFunc(UICCellWidget* From, UICCellWidget* To)
{
	GEngine->AddOnScreenDebugMessage(-1,10.f,FColor::Green,
		FString::Printf(TEXT("from %s to %s"),*From->GetName(),*To->GetName() ));
	OnItemDrop.Broadcast(From, To);
}

/*void UICWidget::OnEquipButtonPressed()
{
	FInventoryCoreDataInfo Items = ParentInventory->GetItems();
}

void UICWidget::OnConsumableButtonPressed()
{
	
}

void UICWidget::OnShowAllButtonPressed()
{
	
}*/
