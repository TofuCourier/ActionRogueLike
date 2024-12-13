// Fill out your copyright notice in the Description page of Project Settings.


#include "ARLMagicProjectile.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "ARLAttributeComponent.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"

AARLMagicProjectile::AARLMagicProjectile()
{
	//SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AARLMagicProjectile::OnActorOverlap);
	SphereComp->IgnoreActorWhenMoving(this, true);
	SphereComp->IgnoreActorWhenMoving(this->GetInstigator(), true);

	AudioComp = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComp"));
	AudioComp->SetupAttachment(RootComponent);
}

void AARLMagicProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if (OtherActor && OtherActor != GetInstigator())
	{
		UARLAttributeComponent* AttributeComp = Cast<UARLAttributeComponent>(OtherActor->GetComponentByClass(UARLAttributeComponent::StaticClass()));
		if (AttributeComp)
		{
			AttributeComp->ApplyHealthChange(-DamageAmount);

			UGameplayStatics::PlaySoundAtLocation(GetWorld(), HitSound, GetActorLocation());

			Destroy();
		}
	}

}

void AARLMagicProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AARLMagicProjectile::OnActorOverlap);

}

void AARLMagicProjectile::BeginPlay()
{
	Super::BeginPlay();

	//AudioComp->Play();
}

void AARLMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
