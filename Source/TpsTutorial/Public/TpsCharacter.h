// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TpsWeapon.h"
#include "TpsCharacter.generated.h"

// Forward declarations
class UCameraComponent;
class USpringArmComponent;
class UTpsHealthComponent;
class UDamageType;
class AController;
class UInputComponent;
class UAnimMontage;

UENUM()
enum EWeaponID
{
	None = -1, LeftWeapon, RightWeapon
};

UCLASS()
class TPSTUTORIAL_API ATpsCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATpsCharacter();

protected:
	// ============== FUNCTIONS ==============

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Shoot weapon function; will be looping if the current weapon is automatic
	UFUNCTION(BlueprintCallable)
	void Fire();

	// dynamic delegate function on health changed
	UFUNCTION()
	void HandleHealthUpdate(UTpsHealthComponent* OwningHealthComp, float CurrentHealth, float HealthDelta, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);

	// Create the crosshair widget in BP
	UFUNCTION(BlueprintImplementableEvent, Category = BlueprintEvents)
	void CreateCrosshairWidgetEvent();

	UFUNCTION(BlueprintCallable)
	void SwapWeaponAction();

	// Bind axis and action inputs
	void StartShoot();
	void EndShoot();
	void ZoomIn();
	void ZoomOut();
	void SwapWeapon();

	// Helper function: Do single line trace by channel, determine end location, and fire weapon
	bool LineTraceFromCameraByChannel(FHitResult& HitResult, FVector& EndLocation, ECollisionChannel TraceChannel);

	// Helper function: Spawn the weapon at the right socket
	void SpawnWeapon();

	UFUNCTION(BlueprintImplementableEvent, Category = "BlueprintEvents")
	void ZoomInCamera();

	UFUNCTION(BlueprintImplementableEvent, Category = "BlueprintEvents")
	void ZoomOutCamera();

	// ================ VARIABLES ================
	// Main camera component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UCameraComponent* CameraComp;

	// Spring Arm component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USpringArmComponent* SpringArmComp;

	// Health component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UTpsHealthComponent* HealthComp;

	// The weapon class to spawn on the left back of character
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	TSubclassOf<ATpsWeapon> LeftWeaponClass;

	// The weapon class to spawn on the right back of character
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	TSubclassOf<ATpsWeapon> RightWeaponClass;

	// The spawned 2 weapon instances and the currently equipped weapon
	UPROPERTY(BlueprintReadOnly, Category = "Weapon")
	TArray<ATpsWeapon*> EquippedWeapons;
	EWeaponID CurrentWeaponID;

	// The animation montage to play when swapping weapons
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	UAnimMontage* WeaponSwapMontage;

	// TThe weapon firing animation montage 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	UAnimMontage* FireWeaponMontage;

	// Whether the player is zooming in
	UPROPERTY(BlueprintReadOnly, Category = "Camera Zoom")
	bool bAiming;

	// The zooming speed
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera Zoom")
	float ZoomSpeed;

	// The FOV after zoom in
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera Zoom")
	float ZoomInFov;

	// The default FOV
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera Zoom")
	float DefaultFov;

	// Whether the character is dead or not
	UPROPERTY(BlueprintReadOnly, Category = "Status")
	bool bDead;

	// The timer handler for shooting weapon
	FTimerHandle TimerHandle;

	// The last fire time
	float LastFireTime;

	// The percentage of zooming (0 by default)
	float ZoomAlpha;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

};
