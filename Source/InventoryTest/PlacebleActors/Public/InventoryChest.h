
#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "InventoryCore/Inventory/Public/InventoryCoreComponent.h"
#include "InventoryCore/Inventory/Public/InventoryCoreManagerComponent.h"
#include "InventoryCore/InventoryWidget/Public/InventoryCoreWidget.h"
#include "InventoryChest.generated.h"


class USphereComponent;


UCLASS()
class INVENTORYTEST_API AInventoryChest : public AActor
{
	GENERATED_BODY()

public:
	
	AInventoryChest();

protected:
	virtual void BeginPlay() override;

protected:

	UPROPERTY(EditAnywhere)
	USphereComponent* Sphere;
	
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* ChestMesh;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UInventoryCoreWidget> ChestWidgetClass;

	UPROPERTY(EditDefaultsOnly)
	UInventoryCoreComponent* ChestInventory;

	UPROPERTY(EditDefaultsOnly)
	UInventoryCoreManagerComponent* ChestManager;

public:

	UInventoryCoreComponent* GetChestInventory() { return ChestInventory; }

	UInventoryCoreManagerComponent* GetChestManager() { return ChestManager; }

protected:
	
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
						int32 OtherBodyIndex, bool bBFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
						UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
