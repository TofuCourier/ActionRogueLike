// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ARLTargetDummy.generated.h"

UCLASS()
class ACTIONROGUELIKE_API AARLTargetDummy : public AActor
{
	GENERATED_BODY()
	
public:	

	AARLTargetDummy();

protected:

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleAnywhere)
	class UARLAttributeComponent* AttributeComp;

	UFUNCTION()
	virtual void PostInitializeComponents() override;

	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, UARLAttributeComponent* OwningComp, float NewHealth, float Delta);



};
