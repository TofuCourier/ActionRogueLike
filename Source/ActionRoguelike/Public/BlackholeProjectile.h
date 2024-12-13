// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ARLBaseProjectile.h"
#include "BlackholeProjectile.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API ABlackholeProjectile : public AARLBaseProjectile
{
	GENERATED_BODY()

	public:

	ABlackholeProjectile();

protected:

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	//class USphereComponent* DestroyComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class URadialForceComponent* RadialForceComp;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;


	
};
