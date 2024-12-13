// Fill out your copyright notice in the Description page of Project Settings.


#include "BlackholeProjectile.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"

ABlackholeProjectile::ABlackholeProjectile()
{
	SphereComp->IgnoreActorWhenMoving(this, true);

	RadialForceComp = CreateDefaultSubobject<URadialForceComponent>(TEXT("RadialForceComp"));
	RadialForceComp->Radius = 100.0f;
	RadialForceComp->SetupAttachment(RootComponent);
	RadialForceComp->ForceStrength = -2000000.0f;
	RadialForceComp->ImpulseStrength = 1000.0f;

}

void ABlackholeProjectile::BeginPlay()
{
	Super::BeginPlay();
}

void ABlackholeProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
