
#include "InventoryTest/Character/Public/ITCharacter.h"
#include "Components/TextBlock.h"
#include "InventoryCore/Inventory/Public/ICEquipComponent.h"
#include "InventoryCore/Inventory/Public/ICManagerComponent.h"
#include "InventoryTest/ITPlayerController.h"
#include "InventoryTest/Component/Public/ITHealthComponent.h"
#include "InventoryTest/HUD/Public/ITHUD.h"
#include "InventoryCore/Inventory/Public/ICComponent.h"
#include "InventoryCore/InventoryWidget/Public/ICEquipWidget.h"
#include "InventoryCore/InventoryWidget/Public/ICWidget.h"
#include "InventoryTest/PlacebleActors/Public/ITChest.h"
#include "Kismet/GameplayStatics.h"
#include "QuestSystem/QuestComponent/Public/QSInteractionComponent.h"


AITCharacter::AITCharacter()
{
	LocalInventory = CreateDefaultSubobject<UICComponent>("LocalInventory");
	EquipInventory = CreateDefaultSubobject<UICEquipComponent>("EquipInventory");
	InventoryManager = CreateDefaultSubobject<UICManagerComponent>("InventoryManager");

	InteractionComponent = CreateDefaultSubobject<UQSInteractionComponent>("Interaction Component");
	InteractionComponent->SetupAttachment(RootComponent);

	HealthComponent = CreateDefaultSubobject<UITHealthComponent>("Health Component");
}

void AITCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Inventory", IE_Pressed, this, &AITCharacter::ShowPlayerInventory);
	PlayerInputComponent->BindAction("NoInventory", IE_Repeat, this, &AITCharacter::HidePlayerInventory);
	
	PlayerInputComponent->BindAction("MediaWidget", IE_Pressed, this, &AITCharacter::ShowMediaWidget);
	PlayerInputComponent->BindAction("HideMediaWidget", IE_Repeat, this, &AITCharacter::HideMediaWidget);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AITCharacter::InteractMe);
}

void AITCharacter::BeginPlay()
{
	Super::BeginPlay();

	if(InventoryManager)
	{
		InventoryManager->Init(LocalInventory);
		InventoryManager->InitEquip(EquipInventory);
	}
}

void AITCharacter::TakeDamage(const FInventoryDamageData& DamageData)
{
	HealthComponent->SetHealth(HealthComponent->GetHealth() - DamageData.Damage);

	if(HealthComponent->GetHealth() <= 0.f)
	{
		if(AITPlayerController* PC = Cast<AITPlayerController>(GetController()))
		{
			if(AITHUD* HUD = Cast<AITHUD>(PC->GetHUD()))
			{
				HUD->ShowWidget(EWidgetID::W_Death_Widget, 0);
			}

			this->DisableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));
			UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetShowMouseCursor(true);
		}
	}
}


void AITCharacter::ShowPlayerInventory()
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


void AITCharacter::HidePlayerInventory()
{
	if(InventoryManager)
	{
		InventoryManager->GetInventoryWidget()->SetVisibility(ESlateVisibility::Collapsed);
		InventoryManager->GetEquipWidget()->SetVisibility(ESlateVisibility::Collapsed);
	}
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetShowMouseCursor(false);
}

void AITCharacter::UseItemFromInventory(UICCellWidget* Item)
{
	FInventoryCoreDataInfo ItemInfo = Item->GetItem();
	
	UICComponent* ItemInventory = Item->GetParentInventory();

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

void AITCharacter::ShowMediaWidget()
{
	if(AITPlayerController* PC = Cast<AITPlayerController>(GetController()))
	{
		if(AITHUD* HUD = Cast<AITHUD>(PC->GetHUD()))
		{
			HUD->ShowWidget(EWidgetID::W_Media_Widget, 0);
			
			UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetShowMouseCursor(true);
		}
	}
}

void AITCharacter::HideMediaWidget()
{
	if(AITPlayerController* PC = Cast<AITPlayerController>(GetController()))
	{
		if(AITHUD* HUD = Cast<AITHUD>(PC->GetHUD()))
		{
			HUD->HideWidget();
			
			UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetShowMouseCursor(false);
		}
	}
}

void AITCharacter::InteractMe()
{
	InteractionComponent->Interact();
}


