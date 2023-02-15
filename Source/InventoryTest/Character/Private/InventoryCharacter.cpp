
#include "InventoryTest/Character/Public/InventoryCharacter.h"
#include "Components/TextBlock.h"
#include "InventoryCore/Inventory/Public/InventoryCoreEquipComponent.h"
#include "InventoryCore/Inventory/Public/InventoryCoreManagerComponent.h"
#include "InventoryTest/InventoryPlayerController.h"
#include "InventoryTest/Component/Public/InventoryHealthComponent.h"
#include "InventoryTest/HUD/Public/InventoryHUD.h"
#include "InventoryCore/Inventory/Public/InventoryCoreComponent.h"
#include "InventoryCore/InventoryWidget/Public/InventoryCoreEquipWidget.h"
#include "InventoryCore/InventoryWidget/Public/InventoryCoreWidget.h"
#include "InventoryTest/PlacebleActors/Public/InventoryChest.h"
#include "Kismet/GameplayStatics.h"


AInventoryCharacter::AInventoryCharacter()
{
	LocalInventory = CreateDefaultSubobject<UInventoryCoreComponent>("LocalInventory");
	EquipInventory = CreateDefaultSubobject<UInventoryCoreEquipComponent>("EquipInventory");
	InventoryManager = CreateDefaultSubobject<UInventoryCoreManagerComponent>("InventoryManager");

	HealthComponent = CreateDefaultSubobject<UInventoryHealthComponent>("Health Component");
}

void AInventoryCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Inventory", IE_Pressed, this, &AInventoryCharacter::ShowPlayerInventory);
	PlayerInputComponent->BindAction("NoInventory", IE_Repeat, this, &AInventoryCharacter::HidePlayerInventory);
}

void AInventoryCharacter::BeginPlay()
{
	Super::BeginPlay();

	if(InventoryManager)
	{
		InventoryManager->Init(LocalInventory);
		InventoryManager->InitEquip(EquipInventory);
		//ChestInventoryManager->Init(Chest->ChestInventory);
	}
}

void AInventoryCharacter::TakeDamage(const FInventoryDamageData& DamageData)
{
	HealthComponent->SetHealth(HealthComponent->GetHealth() - DamageData.Damage);

	if(HealthComponent->GetHealth() <= 0.f)
	{
		if(AInventoryPlayerController* PC = Cast<AInventoryPlayerController>(GetController()))
		{
			if(AInventoryHUD* HUD = Cast<AInventoryHUD>(PC->GetHUD()))
			{
				HUD->ShowWidget(EWidgetID::W_Death_Widget, 0);
			}

			this->DisableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));
			UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetShowMouseCursor(true);
		}
	}
}


void AInventoryCharacter::ShowPlayerInventory()
{
	if(InventoryManager)
	{
		InventoryManager->GetInventoryWidget()->AddToViewport();
		InventoryManager->GetInventoryWidget()->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		InventoryManager->GetEquipWidget()->AddToViewport();
		InventoryManager->GetEquipWidget()->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetShowMouseCursor(true);
}


void AInventoryCharacter::HidePlayerInventory()
{
	if(InventoryManager)
	{
		InventoryManager->GetInventoryWidget()->SetVisibility(ESlateVisibility::Collapsed);
		InventoryManager->GetEquipWidget()->SetVisibility(ESlateVisibility::Collapsed);
	}
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetShowMouseCursor(false);
}

void AInventoryCharacter::UseItemFromInventory(UInventoryCoreCellWidget* Item)
{
	FInventoryCoreDataInfo ItemInfo = Item->GetItem();
	
	UInventoryCoreComponent* ItemInventory = Item->GetParentInventory();

	if(ItemInfo.Type == EItemType::It_Consumable)
	{
		ItemInfo.Count = ItemInfo.Count - 1;
		Item->CountText->SetText(FText::FromString(FString::FromInt(ItemInfo.Count)));
		Item->Clear();
		Item->AddItem(ItemInfo);
		ItemInventory->SetItem(Item->IndexInInventory, ItemInfo);
		HealthComponent->SetHealth(HealthComponent->GetHealth() + 25.f);
	}
}


