// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ARLBaseContainer.h"
#include "ARLGameplayInterface.h"
#include "ARLItemChest.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API AARLItemChest : public AARLBaseContainer, public IARLGameplayInterface
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	float TargetPitch = 110.0f;

	AARLItemChest();

	void Interact_Implementation(APawn* InstigatorPawn) override;

	virtual void Tick(float DeltaTime) override;



protected:
	virtual void BeginPlay() override;


	
};
