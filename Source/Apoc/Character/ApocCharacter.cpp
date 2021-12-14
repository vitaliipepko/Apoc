// Copyright Epic Games, Inc. All Rights Reserved.

#include "ApocCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Apoc/Weapon/WeaponDefault.h"

AApocCharacter::AApocCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AApocCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

	if(CurrentCursor)
	{
		APlayerController* PlayerController = Cast<APlayerController>(GetController());
	
		FHitResult TraceHitResult;
		PlayerController->GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);
		FVector CursorFV = TraceHitResult.ImpactNormal;
		FRotator CursorR = CursorFV.Rotation();
	
		CurrentCursor->SetWorldLocation(TraceHitResult.Location);
		CurrentCursor->SetWorldRotation(CursorR);
	}

	MovementTick(DeltaSeconds);
}

void AApocCharacter::BeginPlay()
{
	Super::BeginPlay();

	InitWeapon();

	if(CursorMaterial)
	{
		CurrentCursor = UGameplayStatics::SpawnDecalAtLocation(GetWorld(), CursorMaterial, CursorSize, FVector(0));
	}
}

void AApocCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &AApocCharacter::InputAxisX);
	PlayerInputComponent->BindAxis("MoveRight", this, &AApocCharacter::InputAxisY);
	
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AApocCharacter::InputAttackPressed);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &AApocCharacter::InputAttackRealesed);
}

void AApocCharacter::InputAxisX(float Amount)
{
	AxisX = Amount;
}
	
void AApocCharacter::InputAxisY(float Amount)
{
	AxisY = Amount;
}

void AApocCharacter::InputAttackPressed()
{
	AttackCharacterEvent(true);
}

void AApocCharacter::InputAttackRealesed()
{
	AttackCharacterEvent(false);
}

void AApocCharacter::MovementTick(float DeltaTime)
{
	AddMovementInput(FVector(1.f, 0.f, 0.f), AxisX);
	AddMovementInput(FVector(0.f, 1.f, 0.f), AxisY);

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if(PlayerController)
	{
		FHitResult HitResult;
		PlayerController->GetHitResultUnderCursor(ECC_GameTraceChannel1, true, HitResult);

		float RotatorYawResult = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), HitResult.Location).Yaw;
		SetActorRotation(FQuat(FRotator(0.f, RotatorYawResult,0.f)));
	}
}

void AApocCharacter::CharacterUpdate()
{
	float PlayerSpeed = 300.f;
	switch (MovementState)
	{
		case EMovementState::Aim_State:
			PlayerSpeed = MovementSpeedInfo.AimSpeed;
			break;
		case EMovementState::Walk_State:
			PlayerSpeed = MovementSpeedInfo.WalkSpeed;
			break;
		case EMovementState::Run_State:
			PlayerSpeed = MovementSpeedInfo.RunSpeed;
			break;
		case EMovementState::AimWalk_State:
			PlayerSpeed = MovementSpeedInfo.AimWalkSpeed;
			break;
		case EMovementState::SprintRun_State:
			PlayerSpeed = MovementSpeedInfo.SprintRunSpeed;
			break;
		default:
			break;
	}

	GetCharacterMovement()->MaxWalkSpeed = PlayerSpeed;
}

void AApocCharacter::ChangeMovementState()
{
	if(!bIsWalk && bIsSprint && bIsAim)
	{
		MovementState = EMovementState::Run_State;
	}
	else
	{
		 if(bIsSprint)
		 {
		 	bIsWalk = false;
		 	bIsAim = false;
		 	MovementState = EMovementState::SprintRun_State;
		}
		if(bIsWalk && ! bIsSprint && !bIsAim)
		{
			MovementState = EMovementState::AimWalk_State;
		}
		else
		{
			if(bIsWalk && !bIsSprint && !bIsAim)
			{
				MovementState = EMovementState::Walk_State;
			}
			else
			{
				if(!bIsWalk && !bIsSprint && bIsAim)
				{
					MovementState = EMovementState::Aim_State;
				}
			}
		}
	}
	CharacterUpdate();
}

void AApocCharacter::InitWeapon()
{
	if(InitWeaponClass)
	{
		FVector SpawnLocation{FVector(0)};
		FRotator SpawnRotation{FRotator(0)};

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Owner = GetOwner();
		SpawnParams.Instigator = GetInstigator();

		AWeaponDefault* MyWeapon = Cast<AWeaponDefault>(GetWorld()->SpawnActor(InitWeaponClass, &SpawnLocation, &SpawnRotation, SpawnParams));
		if(MyWeapon)
		{
			FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
			MyWeapon->AttachToComponent(GetMesh(), AttachmentRules, FName("WeaponSocket"));
			CurrentWeapon = MyWeapon;
		}
	}
}

void AApocCharacter::AttackCharacterEvent(bool bIsFiring)
{
	AWeaponDefault* MyWeapon = GetCurrentWeapon();
	if(MyWeapon)
	{
		MyWeapon->SetWeaponStateFire(bIsFiring);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Null"));
	}
}