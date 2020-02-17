// Fill out your copyright notice in the Description page of Project Settings.


#include "HonkMovementComponent.h"

void UHonkMovementComponent::BeginPlay()
{
	Super::BeginPlay();
	MaxAccelerationUU = MaxAcceleration * METRE_TO_UU;
	BrakingDecelerationUU = BrakingDeceleration * METRE_TO_UU;
	CoastingDecelerationUU = CoastingDeceleration * METRE_TO_UU;
}

void UHonkMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (ThrottleInput > 0)
	{
		ForwardVelocity += MaxAccelerationUU * DeltaTime;
	}
	else if (ThrottleInput < 0)
	{
		if (ForwardVelocity > 0)
		{
			ForwardVelocity -= BrakingDecelerationUU * DeltaTime;
		}
		else
		{
			ForwardVelocity -= MaxAccelerationUU * DeltaTime;
		}
	}
	else
	{
		ForwardVelocity -= CoastingDecelerationUU * DeltaTime;
		if (ForwardVelocity < 0)
		{
			ForwardVelocity = 0;
		}
	}

	GetOwner()->SetActorLocation(GetOwner()->GetActorLocation() += GetOwner()->GetActorForwardVector() * ForwardVelocity);
}

void UHonkMovementComponent::SetThrottleInput(float Val)
{
	ThrottleInput = Val;
}

void UHonkMovementComponent::SetSteeringInput(float Val)
{
	SteeringInput = Val;
}

void UHonkMovementComponent::SetHandbrakeInput(bool bIsBraking)
{
	bIsHandbrakeActive = bIsBraking;
}
