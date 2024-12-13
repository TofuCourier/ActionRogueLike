// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ARLAICharacter.generated.h"

UCLASS()
class ACTIONROGUELIKE_API AARLAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AARLAICharacter();

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Life")
	float LifeSpanOnDeath;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UPawnSensingComponent* PawnSensingComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	class UARLAttributeComponent* AttributeComp;



protected:

	UFUNCTION()
	void OnPawnSeen(APawn* Pawn);

	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, UARLAttributeComponent* OwningComp, float NewHealth, float Delta);

	virtual void PostInitializeComponents() override;
};
