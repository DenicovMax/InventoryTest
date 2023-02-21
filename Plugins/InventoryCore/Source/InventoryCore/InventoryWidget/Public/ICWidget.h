// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ICCellWidget.h"
#include "Blueprint/UserWidget.h"
#include "InventoryCore/Inventory/Public/ICComponent.h"
#include "InventoryCore/Inventory/Public/ICData.h"
#include "ICWidget.generated.h"

class UICManagerComponent;
class UButton;
class UUniformGridPanel;

UCLASS()
class INVENTORYCORE_API UICWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;

	void Init(int32 ItemsCount);

	bool AddItem(const FInventoryCoreDataInfo& Info, int32 SlotIndex);

	FOnItemDrop OnItemDrop;

	UPROPERTY()
	UICComponent* ParentInventory;

protected:

	UPROPERTY(EditDefaultsOnly)
	int32 ItemsInRaw = 10;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UICCellWidget> CellWidgetClass;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
	UUniformGridPanel* CellsPanel;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
	UICCellWidget* GoldCell;

	/*UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
	UButton* EquipButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
	UButton* ConsumableButton;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
	UButton* ShowAllButton;

	UPROPERTY(EditAnywhere)
	UICManagerComponent* ManagerComponent;*/

	UPROPERTY(BlueprintReadWrite)
	TArray<UICCellWidget*> CellWidgets;

	UICCellWidget* CreateCell();

	void InitCell(UICCellWidget* NewCell);

public:
	void OnItemDropFunc(UICCellWidget* From, UICCellWidget* To);
	/*void OnEquipButtonPressed();
	void OnConsumableButtonPressed();
	void OnShowAllButtonPressed();*/

	UICCellWidget* GetCellWidget(int SlotIndex) { return CellWidgets[SlotIndex]; }
};
