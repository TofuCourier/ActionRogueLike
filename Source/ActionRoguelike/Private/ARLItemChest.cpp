// Fill out your copyright notice in the Description page of Project Settings.


#include "ARLItemChest.h"
#include "Components/StaticMeshComponent.h"

AARLItemChest::AARLItemChest()
{
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	RootComponent = BaseMesh;

	LidMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LidMesh"));
	LidMesh->SetupAttachment(RootComponent);
}

void AARLItemChest::Interact_Implementation(APawn* InstigatorPawn)
{
	LidMesh->SetRelativeRotation(FRotator(TargetPitch, 0.0, 0.0));
}

void AARLItemChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AARLItemChest::BeginPlay()
{
	Super::BeginPlay();
}
