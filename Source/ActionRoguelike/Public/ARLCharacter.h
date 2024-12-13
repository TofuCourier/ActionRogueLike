// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ARLCharacter.generated.h"

class UInputAction;
struct FInputActionInstance;
struct FInputActionValue;

UCLASS()
class ACTIONROGUELIKE_API AARLCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AARLCharacter();

protected:

	//UPROPERTY(VisibleAnywhere, Category = "Effects")
	//FName TimeToHitParamName;

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere)
	class UARLInteractionComponent* InteractionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	class UARLAttributeComponent* AttributeComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> Input_Move;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> Input_LookMouse;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> Input_LookStick;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> Input_PrimaryAttack;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> Input_SecondaryAttack;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> Input_Jump;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> Input_Interact;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> Input_Teleport;


	//UPROPERTY(VisibleAnywhere)
	//UActionComponent* ActionComp;

	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AActor> PrimaryProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AActor> SecondaryProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AActor> TeleportProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Attack")
	class UAnimMontage* AttackAnim;

	UPROPERTY(EditAnywhere, Category = "Attack")
	class UParticleSystem* AttackEffect;

	UPROPERTY(EditAnywhere, Category = "Attack")
	float ProjectileRange = 5000.0f;

	FTimerHandle TimerHandle_PrimaryAttack;

	FTimerHandle TimerHandle_SecondaryAttack;

	FTimerHandle TimerHandle_Teleport;



	virtual void BeginPlay() override;

	void Move(const FInputActionInstance& Instance);

	void LookMouse(const FInputActionValue& InputValue);

	void LookStick(const FInputActionValue& InputValue);

	void PrimaryInteract(const FInputActionValue& InputValue);

	void PrimaryAttack(const FInputActionValue& InputValue);

	void PrimaryAttack_TimerELapsed();

	void SecondaryAttack(const FInputActionValue& InputValue);

	void SecondaryAttack_TimerELapsed();

	void Teleport(const FInputActionValue& InputValue);

	void Teleport_TimerElapsed();

	void SpawnProjectile(TSubclassOf<AActor> ClassToSpawn);

	//void SpawnBlackhole(TSubclassOf<AActor> ClassToSpawn);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:

	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, UARLAttributeComponent* OwningComp, float NewHealth, float Delta);

	void AttackStart();

	virtual void PostInitializeComponents() override;




};
