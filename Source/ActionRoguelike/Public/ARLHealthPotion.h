// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ARLBasePotion.h"

#include "ARLHealthPotion.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API AARLHealthPotion : public AARLBasePotion
{
	GENERATED_BODY()

public:

	AARLHealthPotion();

	void Interact_Implementation(APawn* InstigatorPawn) override;

private:

	UPROPERTY(EditAnywhere)
	float HealAmount = 50.0f;

protected:

	FTimerHandle TimerHandle_ReplenishPotion;

	void ReplenishPotion_TimerElapsed();


	
	void ReplenishPotion(bool bActivate);
};
