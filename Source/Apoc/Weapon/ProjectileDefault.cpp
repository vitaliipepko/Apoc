// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileDefault.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"

AProjectileDefault::AProjectileDefault()
{
	PrimaryActorTick.bCanEverTick = true;

	BulletSphereCollision = CreateDefaultSubobject<USphereComponent>("BulletCollision");
	BulletSphereCollision->SetSphereRadius(16.f);
	
	BulletSphereCollision->OnComponentHit.AddDynamic(this, &AProjectileDefault::BulletCollisionSphereHit);
	BulletSphereCollision->OnComponentBeginOverlap.AddDynamic(this, &AProjectileDefault::BulletCollisionSphereBeginOverlap);
	BulletSphereCollision->OnComponentEndOverlap.AddDynamic(this, &AProjectileDefault::BulletCollisionSphereEndOverlap);
	
	BulletSphereCollision->bReturnMaterialOnMove = true;

	BulletSphereCollision->SetCanEverAffectNavigation(false);

	SetRootComponent(BulletSphereCollision);

	BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>("BulletMesh");
	BulletMesh->SetupAttachment(RootComponent);
	BulletMesh->SetCanEverAffectNavigation(false);

	BulletFX = CreateDefaultSubobject<UParticleSystemComponent>("BulletFX");
	BulletFX->SetupAttachment(RootComponent);

	BulletProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("BulletProjectileMovement");
	BulletProjectileMovement->UpdatedComponent = RootComponent;
	BulletProjectileMovement->InitialSpeed = 1.f;
	BulletProjectileMovement->MaxSpeed = 0.f;
	BulletProjectileMovement->bRotationFollowsVelocity = true;
	BulletProjectileMovement->bShouldBounce = true;
}

void AProjectileDefault::BeginPlay()
{
	Super::BeginPlay();
	
}

void AProjectileDefault::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectileDefault::BulletCollisionSphereHit(
		UPrimitiveComponent* HitComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		FVector NormalImpulse,
		const FHitResult& Hit)
{
	
}
	
void AProjectileDefault::BulletCollisionSphereBeginOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	
}
	
void AProjectileDefault::BulletCollisionSphereEndOverlap(
	UPrimitiveComponent* OverlappedActor,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	
}