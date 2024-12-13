// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ARLBaseProjectile.h"
#include "ARLTeleportProjectile.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API AARLTeleportProjectile : public AARLBaseProjectile
{
	GENERATED_BODY()

public:
	AARLTeleportProjectile();

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Teleport")
	float ExplodeDelay = 0.2f;

	UPROPERTY(EditDefaultsOnly, Category = "Teleport")
	float TeleportDelay = 0.2f;

	FTimerHandle TimerHandle_Explode;

	FTimerHandle TimerHandle_Teleport;

	
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void Explode_Implementation() override;

	void TeleportInstigator();
	
};
