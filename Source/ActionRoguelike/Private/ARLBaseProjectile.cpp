// Fill out your copyright notice in the Description page of Project Settings.


#include "ARLBaseProjectile.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Misc/AssertionMacros.h"
#include "ARLAttributeComponent.h"

// Sets default values
AARLBaseProjectile::AARLBaseProjectile()
{
	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComp->SetCollisionProfileName(TEXT("Projectile"));
	RootComponent = SphereComp;

	EffectComp = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("EffectComp"));
	EffectComp->SetupAttachment(RootComponent);

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComp"));
	MovementComp->InitialSpeed = 5000.0f;
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bInitialVelocityInLocalSpace = true;
	MovementComp->ProjectileGravityScale = 0.0f;

}

void AARLBaseProjectile::OnActorHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Explode();
}




void AARLBaseProjectile::Explode_Implementation()
{
	if (IsValid(this))
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, ImpactVFX, GetActorLocation(), GetActorRotation());

		Destroy();
	}
}



// Called when the game starts or when spawned
void AARLBaseProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AARLBaseProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

