// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ARLBaseProjectile.h"
#include "ARLMagicProjectile.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API AARLMagicProjectile : public AARLBaseProjectile
{
	GENERATED_BODY()
	
public:
	AARLMagicProjectile();

protected:

	UPROPERTY(EditAnywhere, Category = "Attack")
	float DamageAmount = 20.0f;

	UPROPERTY(VisibleAnywhere)
	class UAudioComponent* AudioComp;

	UPROPERTY(EditAnywhere, Category = "Sound Effects")
	class USoundBase* HitSound;

	UFUNCTION()
	void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void PostInitializeComponents() override;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
};
