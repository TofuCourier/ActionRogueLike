// Fill out your copyright notice in the Description page of Project Settings.


#include "ARLTeleportProjectile.h"
#include "ARLBaseProjectile.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"

AARLTeleportProjectile::AARLTeleportProjectile()
{
	SphereComp->IgnoreActorWhenMoving(this, true);
}

void AARLTeleportProjectile::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(TimerHandle_Explode, this, &AARLBaseProjectile::Explode, TeleportDelay);
}

void AARLTeleportProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AARLTeleportProjectile::TeleportInstigator()
{
	
	AActor* TeleportingActor = this->GetInstigator();

	if (TeleportingActor)
	{
		bool bTeleported = TeleportingActor->TeleportTo(this->GetActorLocation(), TeleportingActor->GetActorRotation());

	}
}

void AARLTeleportProjectile::Explode_Implementation()
{
	GetWorldTimerManager().ClearTimer(TimerHandle_Explode);

	UGameplayStatics::SpawnEmitterAtLocation(this, ImpactVFX, GetActorLocation(), GetActorRotation());

	EffectComp->DeactivateSystem();

	MovementComp->StopMovementImmediately();
	SetActorEnableCollision(false);

	GetWorldTimerManager().SetTimer(TimerHandle_Teleport, this, &AARLTeleportProjectile::TeleportInstigator, TeleportDelay);


}
