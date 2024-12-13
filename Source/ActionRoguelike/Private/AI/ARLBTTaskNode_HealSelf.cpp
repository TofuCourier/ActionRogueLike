// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/ARLBTTaskNode_HealSelf.h"
#include "AI/ARLAIController.h"
#include "ARLAttributeComponent.h"

EBTNodeResult::Type UARLBTTaskNode_HealSelf::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APawn* AIPawn = Cast<APawn>(OwnerComp.GetAIOwner()->GetPawn());

	if (!AIPawn)
	{
		return EBTNodeResult::Failed;
	}

	UARLAttributeComponent* AttributeComp = Cast<UARLAttributeComponent>(AIPawn->GetComponentByClass(UARLAttributeComponent::StaticClass()));
	if (ensure(AttributeComp))
	{
		AttributeComp->ApplyHealthChange(HealAmount);
	}

	return EBTNodeResult::Succeeded;
}
