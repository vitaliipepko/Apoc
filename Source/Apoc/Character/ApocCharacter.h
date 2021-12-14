// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Types.h"
#include "ApocCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UDecalComponent;
class AWeaponDefault;

UCLASS(Blueprintable)
class AApocCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AApocCharacter();

	virtual void BeginPlay() override;

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Cursor", meta = (AllowPrivateAccess = "true"))
	UDecalComponent* CurrentCursor;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Cursor")
	UMaterialInterface* CursorMaterial = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Cursor")
	FVector CursorSize = FVector(20.f, 40.f, 40.f);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement")
	EMovementState MovementState{EMovementState::Walk_State};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement")
	FCharacterSpeed MovementSpeedInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement")
	bool bIsSprint{false};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement")
	bool bIsWalk{false};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement")
	bool bIsAim{false};

	UPROPERTY()
	AWeaponDefault* CurrentWeapon{nullptr};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Demo")
	TSubclassOf<AWeaponDefault> InitWeaponClass{nullptr};

	UFUNCTION()
	void InputAxisX(float Amount);
	UFUNCTION()
	void InputAxisY(float Amount);

	UFUNCTION()
	void InputAttackPressed();
	UFUNCTION()
	void InputAttackRealesed();

	float AxisX{0.f};
	float AxisY{0.f};
	
	UFUNCTION()
	void MovementTick(float DeltaTime);
	
	UFUNCTION(BlueprintCallable)
	void AttackCharacterEvent(bool bIsFiring);
	UFUNCTION(BlueprintCallable)
	void CharacterUpdate();
	UFUNCTION(BlueprintCallable)
	void ChangeMovementState();

	void InitWeapon();

	FORCEINLINE AWeaponDefault* GetCurrentWeapon() const { return  CurrentWeapon; }

	FORCEINLINE UDecalComponent* GetCursorToWorld() const { return CurrentCursor; }
};
