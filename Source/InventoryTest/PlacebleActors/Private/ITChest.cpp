
#include "InventoryTest/PlacebleActors/Public/ITChest.h"
#include "Chaos/AABBTree.h"
#include "Components/SphereComponent.h"
#include "InventoryCore/Inventory/Public/ICComponent.h"
#include "InventoryCore/Inventory/Public/ICManagerComponent.h"
#include "InventoryCore/InventoryWidget/Public/ICWidget.h"
#include "InventoryTest/Character/Public/ITCharacter.h"


AITChest::AITChest()
{
	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	if(Sphere)
	{
		SetRootComponent(Sphere);
		Sphere->SetCollisionResponseToAllChannels(ECR_Ignore);
		Sphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
		Sphere->SetHiddenInGame(false);
		Sphere->OnComponentBeginOverlap.AddDynamic(this, &AITChest::OnBeginOverlap);
		Sphere->OnComponentEndOverlap.AddDynamic(this, &AITChest::OnEndOverlap);
	}
	
	ChestMesh = CreateDefaultSubobject<UStaticMeshComponent>("Chest Mesh");
	ChestMesh ->SetupAttachment(Sphere);
	
	ChestInventory = CreateDefaultSubobject<UICComponent>("Chest Inventory");
	ChestManager = CreateDefaultSubobject<UICManagerComponent>("Chest Inventory Manager");
}

void AITChest::BeginPlay()
{
	Super::BeginPlay();

	ChestManager->Init(ChestInventory);
}

void AITChest::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bBFromSweep, const FHitResult& SweepResult)
{
	if(AITCharacter* Character = Cast<AITCharacter>(OtherActor))
	{
		ChestManager->GetInventoryWidget()->AddToViewport();
		ChestManager->GetInventoryWidget()->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
}

void AITChest::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(AITCharacter* Character = Cast<AITCharacter>(OtherActor))
	{
		ChestManager->GetInventoryWidget()->SetVisibility(ESlateVisibility::Collapsed);
	}
}

