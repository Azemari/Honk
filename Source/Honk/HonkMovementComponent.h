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
	float MaxAcceleration = 10.0f;

	UPROPERTY(EditAnywhere, Category = "CarStats")
	float CoastingDeceleration = 1.0f;

	UPROPERTY(EditAnywhere, Category = "CarStats")
	float BrakingDeceleration = 20.0f;

private:

	float ForwardVelocity = 0;

	float CoastingDecelerationUU = 0.0f;
	float BrakingDecelerationUU = 0.0f;
	float MaxAccelerationUU = 0.0f;

	float ThrottleInput = 0;
	float SteeringInput = 0;
	bool bIsHandbrakeActive = false;

	const float METRE_TO_UU = 100.f;
};
