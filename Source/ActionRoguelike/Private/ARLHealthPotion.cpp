// Fill out your copyright notice in the Description page of Project Settings.


#include "ARLHealthPotion.h"
#include "ARLAttributeComponent.h"

AARLHealthPotion::AARLHealthPotion()
{

}

void AARLHealthPotion::Interact_Implementation(APawn* InstigatorPawn)
{
	if (InstigatorPawn)
	{
		UARLAttributeComponent* AttributeComp = Cast<UARLAttributeComponent>(InstigatorPawn->GetComponentByClass(UARLAttributeComponent::StaticClass()));
		if (AttributeComp)
		{
			
			AttributeComp->ApplyHealthChange(HealAmount);

			ReplenishPotion(false);

			// Timer to refresh potion
			GetWorldTimerManager().SetTimer(TimerHandle_ReplenishPotion, this, &AARLHealthPotion::ReplenishPotion_TimerElapsed, 10.0f);
		}
	}
}

void AARLHealthPotion::ReplenishPotion_TimerElapsed()
{
	ReplenishPotion(true);
}

void AARLHealthPotion::ReplenishPotion(bool bActivate)
{
	RootComponent->SetVisibility(bActivate, true);
	SetActorEnableCollision(bActivate);

}
