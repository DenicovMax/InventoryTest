
#include "InventoryCore/InventoryWidget/Public/ICCellWidget.h"
#include "InventoryCore/InventoryWidget/Public/ICWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Input/Reply.h"
#include "InventoryCore/Inventory/Public/ICComponent.h"
#include "Kismet/GameplayStatics.h"


struct FInventoryCoreDataInfo;

bool UICCellWidget::AddItem(const FInventoryCoreDataInfo& Info)
{
	if(bHasItem)
	{
		return false;
	}

	if(ItemImage)
	{
		ItemImage->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		ItemImage->SetBrushFromTexture(Info.Icon.LoadSynchronous());
	}

	if(CountText)
	{
		CountText->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		CountText->SetText(FText::FromString(FString::FromInt(Info.Count)));
	}

	bHasItem = true;
	Item = Info;

	return true;
}


void UICCellWidget::Clear()
{
	
	if(ItemImage)
	{
		ItemImage->SetBrushFromTexture(nullptr);
		ItemImage->SetVisibility(ESlateVisibility::Collapsed);
	}

	if(CountText)
	{
		CountText->SetText(FText::FromString(FString::FromInt(0)));
		CountText->SetVisibility(ESlateVisibility::Collapsed);
	}

	Item.ID = NAME_None;

	bHasItem = false;
}


UICComponent* UICCellWidget::GetParentInventory() const
{
	return ParentInventoryWidget ? ParentInventoryWidget->ParentInventory : nullptr; 
}


FReply UICCellWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{	
	if(bCanDrag && bHasItem && InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this,
			EKeys::LeftMouseButton).NativeReply;
	}
	return FReply::Handled();
}

FReply UICCellWidget::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if(bCanDrag && bHasItem)
	{
		/*if(AInventoryCharacter* Character = Cast<AInventoryCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
		{
			Character->UseItemFromInventory(this);
		}*/
	}
	
	return Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);
}


void UICCellWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,
                                                UDragDropOperation*& OutOperation)
{
	OutOperation = UWidgetBlueprintLibrary::CreateDragDropOperation(UDragDropOperation::StaticClass());
	if(OutOperation)
	{
		OutOperation->DefaultDragVisual = this;
	}
	else
	{
		Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
	}
}


bool UICCellWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation)
{
	if(InOperation && InOperation->DefaultDragVisual && InOperation->DefaultDragVisual != this)
	{
		if(UICCellWidget* FromCell = Cast<UICCellWidget>(InOperation->DefaultDragVisual))
		{
			OnItemDrop.Broadcast(FromCell, this);
			return true;
		}
	}
	return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
}

void UICCellWidget::NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragCancelled(InDragDropEvent, InOperation);
}
