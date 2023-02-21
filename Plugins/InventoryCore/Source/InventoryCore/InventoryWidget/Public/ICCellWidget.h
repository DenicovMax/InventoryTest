// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryCore/Inventory/Public/ICData.h"
#include "InventoryCore/Inventory/Public/ICComponent.h"
#include "ICCellWidget.generated.h"

class UImage;
class UTextBlock;
class UICWidget;
class UICComponent;


UCLASS()
class INVENTORYCORE_API UICCellWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UImage* ItemImage;

	bool bHasItem;

	UPROPERTY()
	FInventoryCoreDataInfo Item;

	UPROPERTY()
	UICComponent* Inventory;

public:

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* CountText;

	int32 IndexInInventory = INDEX_NONE;

	bool HasItem() const { return bHasItem; }

	bool AddItem(const FInventoryCoreDataInfo& Info);

	void Clear();

	const FInventoryCoreDataInfo& GetItem() const { return Item; }

	FOnItemDrop OnItemDrop;

	UPROPERTY()
	UICWidget* ParentInventoryWidget;

	UICComponent* GetParentInventory() const;

protected:

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,
	                                  UDragDropOperation*& OutOperation) override;

	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
		UDragDropOperation* InOperation) override;

	UPROPERTY(EditAnywhere)
	bool bCanDrag = true;

public:
	virtual void NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
};
