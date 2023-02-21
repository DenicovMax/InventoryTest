// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ICData.generated.h"



class UICCellWidget;

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnItemDrop, UICCellWidget* /*from*/, UICCellWidget* /*to*/)

UENUM()
enum class EItemType : uint8
{
	It_Misc,
	It_Currency,
	It_Equip,
	It_Consumable
};

UENUM()
enum class EEquipSlot : uint8
{
	Es_Head,
	Es_Body,
	Es_RightHand,
	Es_LeftHand,
	Es_RightFoot,
	Es_LeftFoot,
	Es_None
};

USTRUCT(BlueprintType)
struct INVENTORYCORE_API FInventoryCoreDataInfo : public FTableRowBase
{
	GENERATED_BODY()
public:
	
	UPROPERTY(EditDefaultsOnly, Category = "General")
	int32 Place;

	UPROPERTY(EditDefaultsOnly, Category = "General")
	FName ID;

	UPROPERTY(EditDefaultsOnly, Category = "General")
	FText Name;
	
	UPROPERTY(EditDefaultsOnly, Category = "General")
	int32 Count;

	UPROPERTY(EditDefaultsOnly, Category = "Visual")
	TSoftObjectPtr<UTexture2D> Icon;
	
	UPROPERTY(EditDefaultsOnly, Category = "Type")
	EItemType Type;

	UPROPERTY(EditDefaultsOnly, Category = "Type")
	EEquipSlot EquipSlot;
};


UENUM()
enum class EItemRarity : uint8
{
	Ir_Common,
	Ir_Rare,
	Ir_Epic
};

