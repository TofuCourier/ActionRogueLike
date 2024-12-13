// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ARLGameplayInterface.h"
#include "ARLBasePotion.generated.h"

UCLASS()
class ACTIONROGUELIKE_API AARLBasePotion : public AActor, public IARLGameplayInterface
{
	GENERATED_BODY()

	protected:

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* MeshComp;
	
public:	
	AARLBasePotion();

	void Interact_Implementation(APawn* InstigatorPawn) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
