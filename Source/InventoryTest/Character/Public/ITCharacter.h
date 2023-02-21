
#pragma once

#include "CoreMinimal.h"
#include "ITBaseCharacter.h"
#include "GameFramework/Character.h"
#include "InventoryCore/Inventory/Public/ICManagerComponent.h"
#include "InventoryCore/Inventory/Public/ICComponent.h"
#include "InventoryCore/Inventory/Public/ICEquipComponent.h"
#include "InventoryTest/Interfaces/ITDamageTaker.h"
#include "ITCharacter.generated.h"

class UMediaPlayer;
class UITDeathWidget;
class UITHealthComponent;
class AITChest;

UCLASS()
class AITCharacter : public AITBaseCharacter, public IITDamageTaker
{
	GENERATED_BODY()

public:
	AITCharacter();

	void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	UICEquipComponent* EquipInventory;
	
	UPROPERTY(EditDefaultsOnly)
	UICComponent* LocalInventory;

	UPROPERTY(EditDefaultsOnly)
	UICManagerComponent* InventoryManager;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UITDeathWidget> DeathWidgetClass;
	
	UPROPERTY()
	UITDeathWidget* DeathWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UITHealthComponent* HealthComponent;

	

public:

	virtual void TakeDamage(const FInventoryDamageData& DamageData) override;
	void ShowPlayerInventory();
	void HidePlayerInventory();

	void UseItemFromInventory(UICCellWidget* Item);

	void ShowMediaWidget();
	void HideMediaWidget();
};
