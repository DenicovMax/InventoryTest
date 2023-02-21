
#include "InventoryTest/Component/Public/ITHealthComponent.h"


void UITHealthComponent::SetHealth(float NewHealth)
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

float UITHealthComponent::GetHealth() const
{
	return Health;
}

bool UITHealthComponent::IsDeath() const
{
	return Health <= 0.f;
}


