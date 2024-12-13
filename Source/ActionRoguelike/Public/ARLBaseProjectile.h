// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ARLBaseProjectile.generated.h"

UCLASS()
class ACTIONROGUELIKE_API AARLBaseProjectile : public AActor
{
	GENERATED_BODY()
	
public:	

	AARLBaseProjectile();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USphereComponent* SphereComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UProjectileMovementComponent* MovementComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UParticleSystemComponent* EffectComp;

	UPROPERTY(EditDefaultsOnly)
	class UParticleSystem* ImpactVFX;

	UFUNCTION()
	virtual void OnActorHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	//UFUNCTION()
	//void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);



	virtual void BeginPlay() override;

public:	

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Explode();

	virtual void Tick(float DeltaTime) override;

};
