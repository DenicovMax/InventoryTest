
#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "InventoryCore/Inventory/Public/ICComponent.h"
#include "InventoryCore/Inventory/Public/ICManagerComponent.h"
#include "InventoryCore/InventoryWidget/Public/ICWidget.h"
#include "ITChest.generated.h"


class USphereComponent;


UCLASS()
class INVENTORYTEST_API AITChest : public AActor
{
	GENERATED_BODY()

public:
	
	AITChest();

protected:
	virtual void BeginPlay() override;

protected:

	UPROPERTY(EditAnywhere)
	USphereComponent* Sphere;
	
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* ChestMesh;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UICWidget> ChestWidgetClass;

	UPROPERTY(EditDefaultsOnly)
	UICComponent* ChestInventory;

	UPROPERTY(EditDefaultsOnly)
	UICManagerComponent* ChestManager;

public:

	UICComponent* GetChestInventory() { return ChestInventory; }

	UICManagerComponent* GetChestManager() { return ChestManager; }

protected:
	
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
						int32 OtherBodyIndex, bool bBFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
						UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
