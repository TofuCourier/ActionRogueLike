// Fill out your copyright notice in the Description page of Project Settings.


#include "ARLTargetDummy.h"
#include "Components/StaticMeshComponent.h"
#include "ARLAttributeComponent.h"

// Sets default values
AARLTargetDummy::AARLTargetDummy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;

	AttributeComp = CreateDefaultSubobject<UARLAttributeComponent>(TEXT("AttributeComp"));

}

void AARLTargetDummy::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	AttributeComp->OnHealthChanged.AddDynamic(this, &AARLTargetDummy::OnHealthChanged);

}

void AARLTargetDummy::OnHealthChanged(AActor* InstigatorActor, UARLAttributeComponent* OwningComp, float NewHealth, float Delta)
{
	if (Delta < 0.0f)
	{
		MeshComp->SetScalarParameterValueOnMaterials("TimeToHit", GetWorld()->TimeSeconds);
	}

}

