// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TpsTrackerBot.generated.h"

class UStaticMeshComponent;
class UTpsHealthComponent;
class UDamageType;
class AController;

UCLASS()
class TPSTUTORIAL_API ATpsTrackerBot : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATpsTrackerBot();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	FVector GetNextPathPoint();

	UFUNCTION()
	void HandleOnTakeDamage(UTpsHealthComponent *OwningHealthComp, float CurrentHealth, float HealthDelta, 
			const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UStaticMeshComponent *StaticMeshComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UTpsHealthComponent *HealthComp;

	// Keep track of next path point
	FVector NextPathPoint;

	// The magnitude of Force to apply to this tracker bot
	UPROPERTY(EditDefaultsOnly, Category = "Movements")
	float ForceMag;

	// Whether or not the Force is taken as a change of acceleration instead of force.
	// If true, mass will no effect.
	UPROPERTY(EditDefaultsOnly, Category = "Movements")
	bool bAccelChangeInVelocity;

	// The minimal required distance between this and target.
	// When the distance is smaller than this value, this will get to next path point.
	UPROPERTY(EditDefaultsOnly, Category = "Movements")
	float RequiredDistanceToTarget;

	// The material instance to pulse on taking damage
	UMaterialInstanceDynamic* MatInstance;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


};
