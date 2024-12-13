// Fill out your copyright notice in the Description page of Project Settings.


#include "ARLGameModeBase.h"
#include "EnvironmentQuery/EnvQueryManager.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/EnvQueryInstanceBlueprintWrapper.h"
#include "AI/ARLAICharacter.h"
#include "ARLAttributeComponent.h"
#include "EngineUtils.h"


AARLGameModeBase::AARLGameModeBase()
{
	SpawnTimerInterval = 2.0f;
}

void AARLGameModeBase::StartPlay()
{
	Super::StartPlay();

	// Timer to Spawn bots repeatedly
	GetWorldTimerManager().SetTimer(TimerHandle_SpawnBots, this, &AARLGameModeBase::SpawnBotTimerElapsed, SpawnTimerInterval, true);
}

void AARLGameModeBase::SpawnBotTimerElapsed()
{
	UEnvQueryInstanceBlueprintWrapper* QueryInstWrapper = UEnvQueryManager::RunEQSQuery(this, SpawnBotQuery, this, EEnvQueryRunMode::RandomBest5Pct, nullptr);

	if (ensure(QueryInstWrapper))
	{
		QueryInstWrapper->GetOnQueryFinishedEvent().AddDynamic(this, &AARLGameModeBase::OnQueryCompleted);
	}

}

// Called few frames after we have triggered RunEQSQuery
void AARLGameModeBase::OnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus)
{
	if (!QueryStatus)
	{
		UE_LOG(LogTemp, Warning, TEXT("Spawn Bot EQS Query Failed"));
		return;
	}

	int32 NumOfBotsAlive = 0;
	for (TActorIterator<AARLAICharacter> It(GetWorld()); It; ++It)
	{
		AARLAICharacter* Bot = *It;

		UARLAttributeComponent* AttributeComp = Cast<UARLAttributeComponent>(Bot->GetComponentByClass(UARLAttributeComponent::StaticClass()));
		if (ensure(AttributeComp) && AttributeComp->IsAlive())
		{
			NumOfBotsAlive++;
		}
	}

	float MaxBotCount = 10.0f;

	if (ensure(DifficultyCurve))
	{
		MaxBotCount = DifficultyCurve->GetFloatValue(GetWorld()->TimeSeconds);
	}

	if (NumOfBotsAlive >= MaxBotCount)
	{
		return;
	}

	TArray<FVector> Locations = QueryInstance->GetResultsAsLocations();

	if (Locations.Num() > 0 && Locations.IsValidIndex(0))
	{
		GetWorld()->SpawnActor<AActor>(EnemyClass, Locations[0], FRotator::ZeroRotator);
	}
}
