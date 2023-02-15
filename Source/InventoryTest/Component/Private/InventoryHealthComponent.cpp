
#include "InventoryTest/Component/Public/InventoryHealthComponent.h"


void UInventoryHealthComponent::SetHealth(float NewHealth)
{
	if(Health > 0)
	{
		const float oldHealth = Health;
		Health = FMath::Max(0.f, NewHealth);

		OnHealthChangeDelegate.Broadcast(oldHealth, Health);
		
		if(FMath::IsNearlyZero(Health))
		{
			OnDieDelegate.Broadcast();
		}
	}
}

float UInventoryHealthComponent::GetHealth() const
{
	return Health;
}

bool UInventoryHealthComponent::IsDeath() const
{
	return Health <= 0.f;
}


