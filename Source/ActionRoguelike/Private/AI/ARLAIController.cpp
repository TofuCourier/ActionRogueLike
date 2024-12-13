// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/ARLAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

void AARLAIController::BeginPlay()
{
	Super::BeginPlay();

	if (ensureMsgf(BehaviourTree, TEXT("Behaviour tree is NULL! Assign BehaviorTree in AI Controller!")))
	{
		RunBehaviorTree(BehaviourTree);
	}

	//APawn* MyPawn = UGameplayStatics::GetPlayerPawn(this,0);

	//if (MyPawn)
	//{
	//	GetBlackboardComponent()->SetValueAsVector("MoveToLocation", MyPawn->GetActorLocation());

	//	GetBlackboardComponent()->SetValueAsObject("TargetActor", MyPawn);
	//}
}
