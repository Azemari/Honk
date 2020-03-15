// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PawnMovementComponent.h"
#include "HonkMovementComponent.generated.h"

/**
 * 
 */
UCLASS(config = Game, BlueprintType, Blueprintable, hideCategories = (Navigation), meta = (ShortTooltip = "A Pawn is an actor that can be 'possessed' and receive input from a controller."))
class HONK_API UHonkMovementComponent : public UPawnMovementComponent
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	void SetThrottleInput(float Val);
	void SetSteeringInput(float Val);
	void SetHandbrakeInput(bool bIsBraking);
	void SetIsDrifting(bool bDrifting);
	void CollideWithWall(class AActor* OtherActor, const FHitResult& SweepResult);

protected:
	UPROPERTY(EditAnywhere, Category = "CarStats")
	float MaxAccelerationForward = 10.0f;
	UPROPERTY(EditAnywhere, Category = "CarStats")
	float RateOfAccellerationForward = 2.5f;
	UPROPERTY(EditAnywhere, Category = "CarStats")
	float MaxForwardVelocity = 32.0f;

	UPROPERTY(EditAnywhere, Category = "CarStats")
	float MaxAccelerationBackward = 5.0f;
	UPROPERTY(EditAnywhere, Category = "CarStats")
	float RateOfAccellerationBackward = 1.0f;
	UPROPERTY(EditAnywhere, Category = "CarStats")
	float MaxBackwardVelocity = 9.0f;

	UPROPERTY(EditAnywhere, Category = "CarStats")
	float CoastingDeceleration = 1.0f;

	UPROPERTY(EditAnywhere, Category = "CarStats")
	float BrakingDeceleration = 20.0f;


	UPROPERTY(EditAnywhere, Category = "CarStats")
	float MaxTurnRateDegrees = 1.0f;

	UPROPERTY(EditAnywhere, Category = "CarStats")
	float VelocityForMaxTurnRate = 5.0f;

	UPROPERTY(EditAnywhere, Category = "Drifting")
	float HandbrakeDeceleration = 40.0f;
	UPROPERTY(EditAnywhere, Category = "Drifting")
	float MaxDriftTurnRateDegrees = 1.0f;
	UPROPERTY(EditAnywhere, Category = "Drifting")
	float VelocityForMaxDriftTurnRate = 5.0f;
	UPROPERTY(EditAnywhere, Category = "Drifting")
	float DriftStartTurnMultiplier = 1.5f;
	UPROPERTY(EditAnywhere, Category = "Drifting")
	float MinimumDriftStartVelocity = 25.0f;

	UPROPERTY(EditAnywhere, Category = "Collision")
	float CoefficientOfRestitution = 0.3f;

	UPROPERTY(Transient)
	FVector PrevFrameLocation = FVector::ZeroVector;
	UPROPERTY(Transient)
	FRotator PrevFrameRotation = FRotator::ZeroRotator;

private:

	float Velocity = 0;

	float MaxAccelerationForwardUU = 0.0f;
	float RateOfAccellerationForwardUU = 2.5f;
	float MaxForwardVelocityUU = 32.0f;

	float MaxAccelerationBackwardUU = 5.0f;
	float RateOfAccellerationBackwardUU = 1.0f;
	float MaxBackwardVelocityUU = 9.0f;

	float CoastingDecelerationUU = 0.0f;
	float BrakingDecelerationUU = 0.0f;
	float HandbrakeDecelerationUU = 0.0f;

	float LeftOverDriftVelocity = 0.0f;

	float VelocityForMaxTurnRateUU = 5.0f;
	float VelocityForMaxDriftTurnRateUU = 5.0f;
	float MinimumDriftStartVelocityUU = 0.0f;

	float Accelleration;

	float ThrottleInput = 0;
	float SteeringInput = 0;
	bool bIsHandbrakeActive = false;
	bool bIsDrifting = false;

	float DriftTurn = 0.0f;

	bool bWasThrottlingForward = false;

	void HandleThrottleForwardMovement(float DeltaTime);
	void HandleThrottleMovement(float DeltaTime);
	void HandleDrifting(float DeltaTime);

	const float METRE_TO_UU = 100.f;

	FVector DriftDirection = FVector::ZeroVector;
};
