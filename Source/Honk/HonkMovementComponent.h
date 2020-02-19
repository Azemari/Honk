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
	
	float VelocityForMaxTurnRateUU = 5.0f;

	float Accelleration;

	float ThrottleInput = 0;
	float SteeringInput = 0;
	bool bIsHandbrakeActive = false;

	bool bWasThrottlingForward = false;

	const float METRE_TO_UU = 100.f;
};
