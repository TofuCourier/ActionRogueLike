// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "ARLBTTaskNode_HealSelf.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API UARLBTTaskNode_HealSelf : public UBTTaskNode
{
	GENERATED_BODY()

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere, Category = "AI")
	float HealAmount = 50.0f;
	
};
