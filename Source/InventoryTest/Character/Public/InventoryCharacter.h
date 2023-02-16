
#pragma once

#include "CoreMinimal.h"
#include "InventoryTestCharacter.h"
#include "GameFramework/Character.h"
#include "InventoryCore/Inventory/Public/InventoryCoreManagerComponent.h"
#include "InventoryCore/Inventory/Public/InventoryCoreComponent.h"
#include "InventoryCore/Inventory/Public/InventoryCoreEquipComponent.h"
#include "InventoryTest/Interfaces/IDamageTaker.h"
#include "InventoryCharacter.generated.h"

class UMediaPlayer;
class UInventoryDeathWidget;
class UInventoryHealthComponent;
class AInventoryChest;

UCLASS()
class AInventoryCharacter : public AInventoryTestCharacter, public IIDamageTaker
{
	GENERATED_BODY()

public:
	AInventoryCharacter();

	void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	UInventoryCoreEquipComponent* EquipInventory;
	
	UPROPERTY(EditDefaultsOnly)
	UInventoryCoreComponent* LocalInventory;

	UPROPERTY(EditDefaultsOnly)
	UInventoryCoreManagerComponent* InventoryManager;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UInventoryDeathWidget> DeathWidgetClass;
	
	UPROPERTY()
	UInventoryDeathWidget* DeathWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UInventoryHealthComponent* HealthComponent;

	

public:

	virtual void TakeDamage(const FInventoryDamageData& DamageData) override;
	void ShowPlayerInventory();
	void HidePlayerInventory();

	void UseItemFromInventory(UInventoryCoreCellWidget* Item);

	void ShowMediaWidget();
	void HideMediaWidget();
};
