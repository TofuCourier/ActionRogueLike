// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/ARLAICharacter.h"
#include "Perception/PawnSensingComponent.h"
#include "AI/ARLAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"
#include "ARLAttributeComponent.h"
#include "BrainComponent.h"

AARLAICharacter::AARLAICharacter()
{
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));

	AttributeComp = CreateDefaultSubobject<UARLAttributeComponent>(TEXT("AttributeComp"));

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	LifeSpanOnDeath = 10.0f;

}

void AARLAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	PawnSensingComp->OnSeePawn.AddDynamic(this, &AARLAICharacter::OnPawnSeen);

	AttributeComp->OnHealthChanged.AddDynamic(this, &AARLAICharacter::OnHealthChanged);
}

void AARLAICharacter::OnPawnSeen(APawn* Pawn)
{
	AARLAIController* AIC = Cast<AARLAIController>(GetController());
	if (AIC)
	{
		UBlackboardComponent* BBComp = AIC->GetBlackboardComponent();

		BBComp->SetValueAsObject("TargetActor", Pawn);

	}
}

void AARLAICharacter::OnHealthChanged(AActor* InstigatorActor, UARLAttributeComponent* OwningComp, float NewHealth, float Delta)
{
	// If we are damaged...
	if (Delta < 0.0f)
	{
		// If AI is dead
		if (NewHealth <= 0.0f)
		{
			// Stop running behaviour tree
			AAIController* AIC = Cast<AAIController>(GetController());
			if (AIC)
			{
				// Brain Component is the base of Behaviour Trees
				AIC->GetBrainComponent()->StopLogic(TEXT("Killed"));
			}

			// Ragdoll
			GetMesh()->SetAllBodiesSimulatePhysics(true);
			GetMesh()->SetCollisionProfileName("Ragdoll");

			// Lifespan after dying
			SetLifeSpan(LifeSpanOnDeath);

		}
	}
	if (NewHealth <= 0.0f && Delta < 0.0f)
	{
		APlayerController* PlayerController = Cast<APlayerController>(Controller);
		DisableInput(PlayerController);
	}
}
