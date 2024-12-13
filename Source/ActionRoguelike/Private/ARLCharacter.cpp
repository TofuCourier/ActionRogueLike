// Fill out your copyright notice in the Description page of Project Settings.


#include "ARLCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "ARLInteractionComponent.h"
#include "ARLAttributeComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AARLCharacter::AARLCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->SetupAttachment(RootComponent);

	SpringArmComp->SetUsingAbsoluteRotation(true);

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);

	InteractionComp = CreateDefaultSubobject<UARLInteractionComponent>(TEXT("InteractionComp"));

	AttributeComp = CreateDefaultSubobject<UARLAttributeComponent>(TEXT("AttributeComp"));

	//ActionComp = CreateDefaultSubobject<UActionComponent>(TEXT("ActionComp"));

	GetCharacterMovement()->bOrientRotationToMovement = true;

	//GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;

	//TimeToHitParamName = TEXT("TimeToHit");

}

void AARLCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	AttributeComp->OnHealthChanged.AddDynamic(this, &AARLCharacter::OnHealthChanged);
}

void AARLCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	
}

void AARLCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AARLCharacter::Move(const FInputActionInstance& Instance)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;

	// Get value from input (combined value from WASD keys or single Gamepad stick) and convert to Vector (x,y)
	const FVector2D AxisValue = Instance.GetValue().Get<FVector2D>();

	// Move forward/back
	AddMovementInput(ControlRot.Vector(), AxisValue.Y);

	// Move Right/Left strafe
	const FVector RightVector = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);
	AddMovementInput(RightVector, AxisValue.X);
}

void AARLCharacter::LookMouse(const FInputActionValue& InputValue)
{
	const FVector2D Value = InputValue.Get<FVector2D>();

	AddControllerYawInput(Value.X);
	AddControllerPitchInput(-Value.Y);
}

void AARLCharacter::LookStick(const FInputActionValue& InputValue)
{
	FVector2D Value = InputValue.Get<FVector2D>();

	// Track negative as we'll lose this during the conversion
	bool XNegative = Value.X < 0.f;
	bool YNegative = Value.Y < 0.f;

	// Can further modify with 'sensitivity' settings
	static const float LookYawRate = 100.0f;
	static const float LookPitchRate = 50.0f;

	// non-linear to make aiming a little easier
	Value = Value * Value;

	if (XNegative)
	{
		Value.X *= -1.f;
	}
	if (YNegative)
	{
		Value.Y *= -1.f;
	}

	// Aim assist
	// todo: may need to ease this out and/or change strength based on distance to target
	//float RateMultiplier = 1.0f;
	//if (bHasPawnTarget)
	//{
	//	RateMultiplier = 0.5f;
	//}

	AddControllerYawInput(Value.X * (LookYawRate) * GetWorld()->GetDeltaSeconds());
	AddControllerPitchInput(Value.Y * (LookPitchRate) * GetWorld()->GetDeltaSeconds());
}


void AARLCharacter::PrimaryInteract(const FInputActionValue& InputValue)
{
	if (InteractionComp)
	{
		InteractionComp->PrimaryInteract();
	}
}

void AARLCharacter::PrimaryAttack(const FInputActionValue& InputValue)
{
	AttackStart();

	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &AARLCharacter::PrimaryAttack_TimerELapsed, 0.2F);
	//ActionComp->StartActionByName(this, SharedGameplayTags::Action_PrimaryAttack);
}

void AARLCharacter::PrimaryAttack_TimerELapsed()
{
	if (ensure(PrimaryProjectileClass))
	{
		SpawnProjectile(PrimaryProjectileClass);
	}
}

void AARLCharacter::SecondaryAttack(const FInputActionValue& InputValue)
{
	AttackStart();

	GetWorldTimerManager().SetTimer(TimerHandle_SecondaryAttack, this, &AARLCharacter::SecondaryAttack_TimerELapsed, 0.2f);
}


void AARLCharacter::SecondaryAttack_TimerELapsed()
{
	if (ensure(SecondaryProjectileClass))
	{
		SpawnProjectile(SecondaryProjectileClass);
	}
}

void AARLCharacter::Teleport(const FInputActionValue& InputValue)
{
	AttackStart();
	//PlayAnimMontage(AttackAnim);
	GetWorldTimerManager().SetTimer(TimerHandle_Teleport, this, &AARLCharacter::Teleport_TimerElapsed, 0.2f);
}

void AARLCharacter::Teleport_TimerElapsed()
{
	if (ensure(TeleportProjectileClass))
	{
		SpawnProjectile(TeleportProjectileClass);
	}
}

void AARLCharacter::SpawnProjectile(TSubclassOf<AActor> ClassToSpawn)
{
	AController* OwnerController = GetController();

	if (OwnerController)
	{
		FVector MuzzleLocation = GetMesh()->GetSocketLocation(TEXT("Muzzle_01"));

		UGameplayStatics::SpawnEmitterAttached(AttackEffect, GetMesh(), TEXT("Muzzle_01"));


		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Instigator = this;

		FCollisionShape Shape;
		Shape.SetSphere(20.0f);

		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(this);

		FCollisionObjectQueryParams ObjParams;
		ObjParams.AddObjectTypesToQuery(ECC_WorldStatic);
		ObjParams.AddObjectTypesToQuery(ECC_WorldDynamic);
		ObjParams.AddObjectTypesToQuery(ECC_Pawn);


		FVector Location;
		FRotator Rotation;

		OwnerController->GetPlayerViewPoint(Location, Rotation);


		FVector TraceEnd = Location + Rotation.Vector() * ProjectileRange;

		FHitResult Hit;
		if (GetWorld()->SweepSingleByObjectType(Hit, Location, TraceEnd, FQuat::Identity, ObjParams, Shape, QueryParams))
		{
			TraceEnd = Hit.ImpactPoint;
		}

		FRotator ProjRotation = FRotationMatrix::MakeFromX(TraceEnd - MuzzleLocation).Rotator();


		FTransform SpawnTM = FTransform(ProjRotation, MuzzleLocation);


		AActor* Proj = GetWorld()->SpawnActor<AActor>(ClassToSpawn, SpawnTM, SpawnParams);
	}
}


// Called to bind functionality to input
void AARLCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	const APlayerController* PC = GetController<APlayerController>();
	const ULocalPlayer* LP = PC->GetLocalPlayer();

	UEnhancedInputLocalPlayerSubsystem* Subsystem = LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	check(Subsystem);

	Subsystem->ClearAllMappings();

	// Add mappings for our game, more complex games may have multiple Contexts that are added/removed at runtime
	Subsystem->AddMappingContext(DefaultMappingContext, 0);

	// Checking so we don't crash accidentally
	UEnhancedInputComponent* InputComp = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

	// General
	InputComp->BindAction(Input_Move, ETriggerEvent::Triggered, this, &AARLCharacter::Move);
	InputComp->BindAction(Input_Jump, ETriggerEvent::Triggered, this, &ACharacter::Jump);
	InputComp->BindAction(Input_Interact, ETriggerEvent::Triggered, this, &AARLCharacter::PrimaryInteract);

	// Sprint while key is held
	//InputComp->BindAction(Input_Sprint, ETriggerEvent::Started, this, &ASCharacter::SprintStart);
	//InputComp->BindAction(Input_Sprint, ETriggerEvent::Completed, this, &ASCharacter::SprintStop);

	// MKB
	InputComp->BindAction(Input_LookMouse, ETriggerEvent::Triggered, this, &AARLCharacter::LookMouse);
	// Gamepad
	InputComp->BindAction(Input_LookStick, ETriggerEvent::Triggered, this, &AARLCharacter::LookStick);

	// Abilities
	InputComp->BindAction(Input_PrimaryAttack, ETriggerEvent::Triggered, this, &AARLCharacter::PrimaryAttack);
	InputComp->BindAction(Input_SecondaryAttack, ETriggerEvent::Triggered, this, &AARLCharacter::SecondaryAttack);
	InputComp->BindAction(Input_Teleport, ETriggerEvent::Triggered, this, &AARLCharacter::Teleport);


}

void AARLCharacter::OnHealthChanged(AActor* InstigatorActor, UARLAttributeComponent* OwningComp, float NewHealth, float Delta)
{
	if (Delta < 0.0f)
	{/*
		UMaterialInstanceDynamic* MaterialInstance = GetMesh()->CreateAndSetMaterialInstanceDynamic(0);
		if (!MaterialInstance)
		{
			return;
		}*/
		GetMesh()->SetScalarParameterValueOnMaterials("TimeToHit", GetWorld()->TimeSeconds);
	}
	if (NewHealth <= 0.0f && Delta < 0.0f)
	{
		APlayerController* PlayerController = Cast<APlayerController>(Controller);
		DisableInput(PlayerController);
	}
}


void AARLCharacter::AttackStart()
{
	PlayAnimMontage(AttackAnim);

	UGameplayStatics::SpawnEmitterAttached(AttackEffect, GetMesh(), TEXT("Muzzle_01"));
}


