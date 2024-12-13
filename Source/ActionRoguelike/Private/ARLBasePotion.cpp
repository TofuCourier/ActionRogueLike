// Fill out your copyright notice in the Description page of Project Settings.


#include "ARLBasePotion.h"
#include "Components/StaticMeshComponent.h"
#include "ARLAttributeComponent.h"


// Sets default values
AARLBasePotion::AARLBasePotion()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AARLBasePotion::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AARLBasePotion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AARLBasePotion::Interact_Implementation(APawn* InstigatorPawn)
{

}

