// Fill out your copyright notice in the Description page of Project Settings.


#include "ARLAttributeComponent.h"

// Sets default values for this component's properties
UARLAttributeComponent::UARLAttributeComponent()
{
	Health = 100.0f;

	MaxHealth = Health;
}


bool UARLAttributeComponent::IsAlive() const 
{
	return Health > 0.0f;
}

bool UARLAttributeComponent::IsAtFullHealth() const
{
	return Health >= MaxHealth || FMath::IsNearlyEqual(Health, MaxHealth);
}

bool UARLAttributeComponent::ApplyHealthChange(float Delta)
{
	float OldHealth = Health;

	Health = FMath::Clamp(Health + Delta, 0.0f, MaxHealth);

	// If health is at 0, return false
	float RealDelta = Health - OldHealth;

	OnHealthChanged.Broadcast(nullptr, this, Health, RealDelta);

	return RealDelta != 0;
}

