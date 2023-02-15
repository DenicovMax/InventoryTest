
#include "InventoryTest/PlacebleActors/Public/InventoryChest.h"
#include "Chaos/AABBTree.h"
#include "Components/SphereComponent.h"
#include "InventoryCore/Inventory/Public/InventoryCoreComponent.h"
#include "InventoryCore/Inventory/Public/InventoryCoreManagerComponent.h"
#include "InventoryCore/InventoryWidget/Public/InventoryCoreWidget.h"
#include "InventoryTest/Character/Public/InventoryCharacter.h"


AInventoryChest::AInventoryChest()
{
	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	if(Sphere)
	{
		SetRootComponent(Sphere);
		Sphere->SetCollisionResponseToAllChannels(ECR_Ignore);
		Sphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
		Sphere->SetHiddenInGame(false);
		Sphere->OnComponentBeginOverlap.AddDynamic(this, &AInventoryChest::OnBeginOverlap);
		Sphere->OnComponentEndOverlap.AddDynamic(this, &AInventoryChest::OnEndOverlap);
	}
	
	ChestMesh = CreateDefaultSubobject<UStaticMeshComponent>("Chest Mesh");
	ChestMesh ->SetupAttachment(Sphere);
	
	ChestInventory = CreateDefaultSubobject<UInventoryCoreComponent>("Chest Inventory");
	ChestManager = CreateDefaultSubobject<UInventoryCoreManagerComponent>("Chest Inventory Manager");
}

void AInventoryChest::BeginPlay()
{
	Super::BeginPlay();

	ChestManager->Init(ChestInventory);
}

void AInventoryChest::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bBFromSweep, const FHitResult& SweepResult)
{
	if(AInventoryCharacter* Character = Cast<AInventoryCharacter>(OtherActor))
	{
		ChestManager->GetInventoryWidget()->AddToViewport();
		ChestManager->GetInventoryWidget()->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
}

void AInventoryChest::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(AInventoryCharacter* Character = Cast<AInventoryCharacter>(OtherActor))
	{
		ChestManager->GetInventoryWidget()->SetVisibility(ESlateVisibility::Collapsed);
	}
}

