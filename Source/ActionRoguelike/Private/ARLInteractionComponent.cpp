// Fill out your copyright notice in the Description page of Project Settings.


#include "ARLInteractionComponent.h"
#include "ARLGameplayInterface.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UARLInteractionComponent::UARLInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UARLInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UARLInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void UARLInteractionComponent::PrimaryInteract()
{
	FCollisionObjectQueryParams ObjectsQueryParams;
	ObjectsQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	
	AActor* MyOwner = GetOwner();

	FVector EyeLocation;
	FRotator EyeRotation;
	MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

	FVector EndLocation = EyeLocation + (EyeRotation.Vector() * 400);


	// Version 1
	//FHitResult Hit;
	// 
	//bool bBlockingHit = GetWorld()->LineTraceSingleByObjectType(Hit, EyeLocation, EndLocation, ObjectsQueryParams);

	//AActor* HitActor = Hit.GetActor();
	//if (HitActor)
	//{
	//	if (HitActor->Implements<UARLGameplayInterface>())
	//	{
	//		APawn* MyPawn = Cast<APawn>(MyOwner);

	//		IARLGameplayInterface::Execute_Interact(HitActor, MyPawn);
	//	}
	//}

	// Version 2
	TArray<FHitResult> Hits;

	FCollisionShape Shape;
	float SphereRadius = 30.0f;
	Shape.SetSphere(SphereRadius);

	bool bBlockingHit = GetWorld()->SweepMultiByObjectType(Hits, EndLocation, EndLocation, FQuat::Identity, ObjectsQueryParams, Shape);

	FColor LineColor = bBlockingHit ? FColor::Green : FColor::Red;
	for (FHitResult Hit : Hits)
	{
		AActor* HitActor = Hit.GetActor();
		if (HitActor)
		{
			if (HitActor->Implements<UARLGameplayInterface>())
			{
				APawn* MyPawn = Cast<APawn>(MyOwner);

				IARLGameplayInterface::Execute_Interact(HitActor, MyPawn);
				//break;
			}
		}
		DrawDebugSphere(GetWorld(), Hit.ImpactPoint, SphereRadius, 32.0f, LineColor, false, 2.0f);
	}



	DrawDebugLine(GetWorld(), EyeLocation, EndLocation, LineColor, false, 2.0f, 0, 2.0f);
}
