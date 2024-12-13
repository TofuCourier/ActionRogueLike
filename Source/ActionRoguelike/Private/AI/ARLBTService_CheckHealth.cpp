// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/ARLBTService_CheckHealth.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "ARLAttributeComponent.h"

UARLBTService_CheckHealth::UARLBTService_CheckHealth()
{
	MinHealthPercentage = 0.50f;
}

void UARLBTService_CheckHealth::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UBlackboardComponent* BBComp = OwnerComp.GetBlackboardComponent();

	if (ensure(BBComp))
	{
		APawn* AIPawn = OwnerComp.GetAIOwner()->GetPawn();
		if (ensure(AIPawn))
		{
			UARLAttributeComponent* AttributeComp = Cast<UARLAttributeComponent>(AIPawn->FindComponentByClass(UARLAttributeComponent::StaticClass()));

			if (ensure(AttributeComp))
			{
				float HealthThreshold = AttributeComp->GetMaxHealth() * MinHealthPercentage;

				// Check if current health is below the calculated threshold
				bool bIsHealthLow = AttributeComp->GetHealth() < HealthThreshold;

				// Update the blackboard key
				BBComp->SetValueAsBool(HealthKey.SelectedKeyName, bIsHealthLow);

				//UE_LOG(LogTemp, Warning, TEXT("Health Below Threshold: %s"), bIsHealthLow ? TEXT("TRUE") : TEXT("FALSE"));
			}
		}
	}
}
