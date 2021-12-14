// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponDefault.h"

#include "ProjectileDefault.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

AWeaponDefault::AWeaponDefault()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);

	SkeletalMeshWeapon = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMeshComponent");
	SkeletalMeshWeapon->SetGenerateOverlapEvents(false);
	SkeletalMeshWeapon->SetCollisionProfileName("NoCollision");
	SkeletalMeshWeapon->SetupAttachment(RootComponent);

	// StaticMeshWeapon = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	// StaticMeshWeapon->SetGenerateOverlapEvents(false);
	// StaticMeshWeapon->SetCollisionProfileName("NoCollision");
	// StaticMeshWeapon->SetupAttachment(RootComponent);

	ShootLocation = CreateDefaultSubobject<UArrowComponent>("ShootLocation");
	ShootLocation->SetupAttachment(RootComponent);
}

void AWeaponDefault::BeginPlay()
{
	Super::BeginPlay();

	check(SkeletalMeshWeapon);

	//WeaponInit();
}

void AWeaponDefault::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FireTick(DeltaTime);
}

void AWeaponDefault::FireTick(float DeltaTime)
{
	if(bIsWeaponFiring)
	{
		if(FireTime < 0.f)
		{
			Fire();
		}
		else
		{
			FireTime -= DeltaTime;
		}
	}
}

// void AWeaponDefault::WeaponInit()
// {
// 	if(SkeletalMeshWeapon && !SkeletalMeshWeapon->SkeletalMesh)
// 	{
// 		SkeletalMeshWeapon->DestroyComponent(true);
// 	}
//
// 	if(StaticMeshWeapon && !StaticMeshWeapon->GetStaticMesh())
// 	{
// 		StaticMeshWeapon->DestroyComponent();
// 	}
// }

void AWeaponDefault::SetWeaponStateFire(bool bIsFire)
{
	if(CheckWeaponCanFire())
	{
		bIsWeaponFiring = bIsFire;
	}
	else
	{
		bIsWeaponFiring = false;
	}
}

bool AWeaponDefault::CheckWeaponCanFire()
{
	return true;
}

FProjectileSettings AWeaponDefault::GetProjectile()
{
	return WeaponSettings.ProjectileSettings;
}

void AWeaponDefault::Fire()
{
	FireTime = WeaponSettings.RateOfFire;

	if(ShootLocation)
	{
		FVector SpawnLocation{ShootLocation->GetComponentLocation()};
		FRotator SpawnRotation{ShootLocation->GetComponentRotation()};
		FProjectileSettings ProjectileSettings;
		ProjectileSettings = GetProjectile();

		if(ProjectileSettings.Projectile)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			SpawnParams.Owner = GetOwner();
			SpawnParams.Instigator = GetInstigator();

			AProjectileDefault* MyProjectile = Cast<AProjectileDefault>(GetWorld()->SpawnActor(ProjectileSettings.Projectile, &SpawnLocation, &SpawnRotation, SpawnParams));
			if(MyProjectile)
			{
				//TODO Init Projectile Settings By Id In Table Row(Or Keep In Weapon Table)
				MyProjectile->InitialLifeSpan = 10.f;
				//MyProjectile->BulletProjectileMovement->InitialSpeed = 2500.f;
			}
		}
		else
		{
			//TODO Projectile Null Init Trace Fire
		}		
	}
}