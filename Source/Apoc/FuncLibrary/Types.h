// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Types.generated.h"

UENUM(BlueprintType)
enum class EMovementState : uint8
{
	Aim_State UMETA(DisplayName = "Aim State"),
	AimWalk_State UMETA(DisplayName = "AimWalk_State"),
	Walk_State UMETA(DisplayName = "Walk State"),
	Run_State UMETA(DisplayName = "Run State"),
	SprintRun_State UMETA(DisplayName = "Run State")
};

USTRUCT(BlueprintType)
struct FCharacterSpeed
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement")
	float AimSpeed{300.f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement")
	float WalkSpeed{300.f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement")
	float AimWalkSpeed{300.f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement")
	float RunSpeed{300.f};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement")
	float SprintRunSpeed{600.f};
};

class AProjectileDefault;

USTRUCT(BlueprintType)
struct FProjectileSettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProjectileSettings")
	TSubclassOf<AProjectileDefault> Projectile{nullptr};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProjectileSettings")
	float ProjectileDamage{20.f};
};

USTRUCT(BlueprintType)
struct FWeaponSettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponSettings")
	float WeaponDamage{20.f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponSettings")
	float RateOfFire{0.5f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponSettings")
	FProjectileSettings ProjectileSettings;
};