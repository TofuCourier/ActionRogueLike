// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/ARLBTService_CheckAttackRange.h"
#include "AI/ARLBTService_CheckAttackRange.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

void UARLBTService_CheckAttackRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	// Get Distance between AI Actor and Target Actor

	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();

	// Ensure we have the component in the owner
	if (ensure(BlackboardComp))
	{
		// Get the actor in TargetActor
		AActor* TargetActor = Cast<AActor>(BlackboardComp->GetValueAsObject("TargetActor"));
		if (!TargetActor)
		{
			return;
		}

		// Get Owning AI Controller
		AAIController* MyAIController = OwnerComp.GetAIOwner();
		if (ensure(MyAIController))
		{
			APawn* AIPawn = MyAIController->GetPawn();
			if (ensure(AIPawn))
			{
				float DistanceTo = FVector::Distance(TargetActor->GetActorLocation(), AIPawn->GetActorLocation());

				bool bWithinRange = DistanceTo < 4000.0f;

				bool bLineOfSight = false;
				if (bWithinRange)
				{
					bLineOfSight = MyAIController->LineOfSightTo(TargetActor);
				}


				BlackboardComp->SetValueAsBool(AttackRangeKey.SelectedKeyName, (bWithinRange && bLineOfSight));
			}
		}
	}

}
