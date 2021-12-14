// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Types.h"
#include "GameFramework/Actor.h"
#include "WeaponDefault.generated.h"

class USceneComponent;
class USkeletalMeshComponent;
class UStaticMeshComponent;
class UArrowComponent;

UCLASS()
class APOC_API AWeaponDefault : public AActor
{
	GENERATED_BODY()
	
public:	
	AWeaponDefault();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* SceneComponent{nullptr};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* SkeletalMeshWeapon{nullptr};

	// UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	// UStaticMeshComponent* StaticMeshWeapon{nullptr};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UArrowComponent* ShootLocation{nullptr};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponSettings")
	FWeaponSettings WeaponSettings;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	void FireTick(float DeltaTime);

	void WeaponInit();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponSettings")
	bool bIsWeaponFiring{false};

	UFUNCTION(BlueprintCallable)
	void SetWeaponStateFire(bool bIsFire);

	bool CheckWeaponCanFire();
	
	FProjectileSettings GetProjectile();
	
	void Fire();

	float FireTime{0.f};
};
