// Fill out your copyright notice in the Description page of Project Settings.


#include "HonkMovementComponent.h"

void UHonkMovementComponent::BeginPlay()
{
	Super::BeginPlay();
	MaxAccelerationForwardUU = MaxAccelerationForward * METRE_TO_UU;
	RateOfAccellerationForwardUU = RateOfAccellerationForward * METRE_TO_UU;
	MaxForwardVelocityUU = MaxForwardVelocity * METRE_TO_UU;

	MaxAccelerationBackwardUU = MaxAccelerationBackward * METRE_TO_UU;
	RateOfAccellerationBackwardUU = RateOfAccellerationBackward * METRE_TO_UU;
	MaxBackwardVelocityUU = MaxBackwardVelocity * METRE_TO_UU;

	VelocityForMaxTurnRateUU = VelocityForMaxTurnRate * METRE_TO_UU;

	BrakingDecelerationUU = BrakingDeceleration * METRE_TO_UU;
	HandbrakeDecelerationUU = HandbrakeDeceleration * METRE_TO_UU;
	CoastingDecelerationUU = CoastingDeceleration * METRE_TO_UU;

	HandbrakeAccellerationBuildupUU = HandbrakeAccellerationBuildup * METRE_TO_UU;
	HandbrakeAccellerationCapUU = HandbrakeAccellerationCap * METRE_TO_UU;

	VelocityForMaxDriftTurnRateUU = VelocityForMaxDriftTurnRate * METRE_TO_UU;
}

void UHonkMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (bIsHandbrakeActive)
	{
		HandleHandbrakeMovement(DeltaTime, Velocity);
	}
	else
	{
		HandleThrottleMovement(DeltaTime);
		if (LeftOverDriftVelocity != 0.0f)
		{
			HandleHandbrakeMovement(DeltaTime, LeftOverDriftVelocity);
		}
	}
}

void UHonkMovementComponent::HandleThrottleMovement(float DeltaTime)
{
	if (ThrottleInput > 0)
	{
		bWasThrottlingForward = true;

		if (Accelleration < 0)
		{
			Accelleration = 0;
		}

		Accelleration += RateOfAccellerationForwardUU;
		if (Accelleration > MaxAccelerationForwardUU)
		{
			Accelleration = MaxAccelerationForwardUU;
		}

		Velocity += Accelleration * ThrottleInput * DeltaTime;
		if (Velocity > MaxForwardVelocityUU)
		{
			Velocity = MaxForwardVelocityUU;
		}
	}
	else if (ThrottleInput < 0)
	{
		if (Accelleration > 0)
		{
			Accelleration = 0;
		}

		if (Velocity > 0)
		{
			Velocity += BrakingDecelerationUU * ThrottleInput * DeltaTime;
		}
		else
		{
			bWasThrottlingForward = false;
			Accelleration -= RateOfAccellerationBackwardUU;
			if (Accelleration < -1.0f * RateOfAccellerationBackwardUU)
			{
				Accelleration = -1.0f * RateOfAccellerationBackwardUU;
			}

			Velocity -= Accelleration * ThrottleInput * DeltaTime;
			if (Velocity < MaxBackwardVelocityUU * -1.f)
			{
				Velocity = MaxBackwardVelocityUU * -1.f;
			}
		}
	}
	else
	{
		Accelleration = 0;
		if (bWasThrottlingForward)
		{
			Velocity -= CoastingDecelerationUU * DeltaTime;
			if (Velocity < 0)
			{
				Velocity = 0;
			}
		}
		else
		{
			Velocity += CoastingDecelerationUU * DeltaTime;
			if (Velocity > 0)
			{
				Velocity = 0;
			}
		}
	}

	if (Velocity != 0.0f)
	{
		FRotator NewRot = GetOwner()->GetActorRotation();
		float VelocityTurnMult = (Velocity / VelocityForMaxTurnRateUU);
	
		NewRot.Add(0.0f, MaxTurnRateDegrees * SteeringInput * DeltaTime * VelocityTurnMult, 0.0f);
		GetOwner()->SetActorRotation(NewRot);
	}
	GetOwner()->SetActorLocation(GetOwner()->GetActorLocation() += GetOwner()->GetActorForwardVector() * Velocity * DeltaTime);
}

void UHonkMovementComponent::HandleHandbrakeMovement(float DeltaTime, float& VelocityToUse)
{
	if (VelocityToUse != 0.0f)
	{
		Accelleration = 0.0f;
		FRotator NewRot = GetOwner()->GetActorRotation();
		float VelocityTurnMult = (VelocityToUse / VelocityForMaxDriftTurnRateUU);

		NewRot.Add(0.0f, MaxDriftTurnRateDegrees * SteeringInput * DeltaTime * VelocityTurnMult, 0.0f);
		GetOwner()->SetActorRotation(NewRot);
		
		if (VelocityToUse > 0.0f)
		{
			VelocityToUse -= HandbrakeDecelerationUU * DeltaTime;
			if (VelocityToUse < 0.0f)
			{
				VelocityToUse = 0.0f;
			}
		}
		else
		{
			VelocityToUse += HandbrakeDecelerationUU * DeltaTime;
			if (VelocityToUse > 0.0f)
			{
				VelocityToUse = 0.0f;
			}
		}

		GetOwner()->SetActorLocation(GetOwner()->GetActorLocation() += HandbrakeDirection * VelocityToUse * DeltaTime);
	}
	else if (ThrottleInput != 0)
	{
		Accelleration += HandbrakeAccellerationBuildupUU * DeltaTime * ThrottleInput;
		if (Accelleration > HandbrakeAccellerationCapUU)
		{
			Accelleration = HandbrakeAccellerationCapUU;
		}
		else if (Accelleration < -HandbrakeAccellerationCapUU)
		{
			Accelleration = HandbrakeAccellerationCapUU * -1.0f;
		}
	}
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
	if (bIsHandbrakeActive)
	{
		HandbrakeDirection = GetOwner()->GetActorForwardVector();
	}
	else
	{
		LeftOverDriftVelocity = Velocity;
		Velocity = 0.0f;	
	}
}
