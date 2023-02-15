// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryCoreCellWidget.h"
#include "Blueprint/UserWidget.h"
#include "InventoryCore/Inventory/Public/InventoryCoreComponent.h"
#include "InventoryCore/Inventory/Public/InventoryCoreData.h"
#include "InventoryCoreWidget.generated.h"

class UInventoryCoreManagerComponent;
class UButton;
class UUniformGridPanel;

UCLASS()
class INVENTORYCORE_API UInventoryCoreWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;;

	void Init(int32 ItemsCount);

	bool AddItem(const FInventoryCoreDataInfo& Info, int32 SlotIndex);

	FOnItemDrop OnItemDrop;

	UPROPERTY()
	UInventoryCoreComponent* ParentInventory;

protected:

	UPROPERTY(EditDefaultsOnly)
	int32 ItemsInRaw = 10;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UInventoryCoreCellWidget> CellWidgetClass;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
	UUniformGridPanel* CellsPanel;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
	UInventoryCoreCellWidget* GoldCell;

	/*UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
	UButton* EquipButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
	UButton* ConsumableButton;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
	UButton* ShowAllButton;

	UPROPERTY(EditAnywhere)
	UInventoryCoreManagerComponent* ManagerComponent;*/

	UPROPERTY(BlueprintReadWrite)
	TArray<UInventoryCoreCellWidget*> CellWidgets;

	UInventoryCoreCellWidget* CreateCell();

	void InitCell(UInventoryCoreCellWidget* NewCell);

public:
	void OnItemDropFunc(UInventoryCoreCellWidget* From, UInventoryCoreCellWidget* To);
	/*void OnEquipButtonPressed();
	void OnConsumableButtonPressed();
	void OnShowAllButtonPressed();*/

	UInventoryCoreCellWidget* GetCellWidget(int SlotIndex) { return CellWidgets[SlotIndex]; }
};
