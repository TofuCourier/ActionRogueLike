// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ARLBaseContainer.generated.h"

class UStaticMeshComponent;

UCLASS()
class ACTIONROGUELIKE_API AARLBaseContainer : public AActor
{
	GENERATED_BODY()
	
public:	
	AARLBaseContainer();

protected:

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(BlueprintReadWrite)
	UStaticMeshComponent* LidMesh;


	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
