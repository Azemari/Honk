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

	MinimumDriftStartVelocityUU = MinimumDriftStartVelocity * METRE_TO_UU;

	VelocityForMaxDriftTurnRateUU = VelocityForMaxDriftTurnRate * METRE_TO_UU;
}

void UHonkMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (bIsDrifting)
	{
		HandleDrifting(DeltaTime);
	}
	else
	{
		HandleThrottleMovement(DeltaTime);
		if (LeftOverDriftVelocity > 0.0f)
		{
			if (DriftTurn > 90.0f)
			{
				DriftDirection = GetOwner()->GetActorRightVector() * -1.0f;
			}
			else if (DriftTurn < -90.0f)
			{
				DriftDirection = GetOwner()->GetActorRightVector();
			}

			if (LeftOverDriftVelocity > 0.0f)
			{
				LeftOverDriftVelocity -= HandbrakeDecelerationUU * DeltaTime;
				if (LeftOverDriftVelocity < 0.0f)
				{
					LeftOverDriftVelocity = 0.0f;
				}
			}
			GetOwner()->SetActorLocation(GetOwner()->GetActorLocation() += DriftDirection * LeftOverDriftVelocity * DeltaTime);
		}
	}
}

void UHonkMovementComponent::HandleThrottleForwardMovement(float DeltaTime)
{
	if (Accelleration < 0)
	{
		Accelleration = 0;
	}

	Accelleration += RateOfAccellerationForwardUU;
	if (Accelleration > MaxAccelerationForwardUU)
	{
		Accelleration = MaxAccelerationForwardUU;
	}

	if (!bIsHandbrakeActive || bIsDrifting)
	{
		Velocity += Accelleration * ThrottleInput * DeltaTime;
		if (Velocity > MaxForwardVelocityUU)
		{
			Velocity = MaxForwardVelocityUU;
		}
	}
	else
	{
		Velocity -= HandbrakeDecelerationUU * DeltaTime;
		if (Velocity < 0)
		{
			Velocity = 0;
		}
	}
}

void UHonkMovementComponent::HandleThrottleMovement(float DeltaTime)
{
	if (ThrottleInput > 0)
	{
		bWasThrottlingForward = true;
		HandleThrottleForwardMovement(DeltaTime);		
	}
	else if (bIsHandbrakeActive)
	{
		if (Velocity > 0.0f)
		{
			Velocity -= HandbrakeDecelerationUU * DeltaTime;
			if (Velocity < 0)
			{
				Velocity = 0;
			}
		}
		else
		{
			Velocity += HandbrakeDecelerationUU * DeltaTime;
			if (Velocity > 0)
			{
				Velocity = 0;
			}
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
		float VelocityTurnMult = FMath::Min((Velocity / VelocityForMaxTurnRateUU), 1.0f);
	
		NewRot.Add(0.0f, MaxTurnRateDegrees * SteeringInput * DeltaTime * VelocityTurnMult, 0.0f);
		GetOwner()->SetActorRotation(NewRot);
	}
	GetOwner()->SetActorLocation(GetOwner()->GetActorLocation() += GetOwner()->GetActorForwardVector() * Velocity * DeltaTime);
}

void UHonkMovementComponent::HandleDrifting(float DeltaTime)
{
	if (SteeringInput == 0.0f || Velocity == 0.0f)
	{
		SetIsDrifting(false);
		return;
	}
	
	float TurnMult = 1.0f;
	if (DriftTurn > 90.0f)
	{
		DriftDirection = GetOwner()->GetActorRightVector() * -1.0f;
	}
	else if (DriftTurn < -90.0f)
	{
		DriftDirection = GetOwner()->GetActorRightVector();
	}
	else
	{
		TurnMult = DriftStartTurnMultiplier;
	}

	FRotator NewRot = GetOwner()->GetActorRotation();
	float VelocityTurnMult = FMath::Min((Velocity / VelocityForMaxDriftTurnRateUU), 1.0f);
	float DriftIncrement = MaxDriftTurnRateDegrees * SteeringInput * DeltaTime * TurnMult * VelocityTurnMult;
	DriftTurn += DriftIncrement;
	NewRot.Add(0.0f, DriftIncrement, 0.0f);
	GetOwner()->SetActorRotation(NewRot);

	if (ThrottleInput >= 0 )
	{
		HandleThrottleForwardMovement(DeltaTime);
	}


	GetOwner()->SetActorLocation(GetOwner()->GetActorLocation() += DriftDirection * Velocity * DeltaTime);
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
	if (SteeringInput != 0 && bIsHandbrakeActive && Velocity >= MinimumDriftStartVelocityUU)
	{
		SetIsDrifting(true);
	}
	else
	{
		SetIsDrifting(false);
	}
}

void UHonkMovementComponent::SetIsDrifting(bool bDrifting)
{
	if (bIsDrifting != bDrifting)
	{
		bIsDrifting = bDrifting;
		if (bIsDrifting)
		{
			DriftTurn = 0.0f;
			DriftDirection = GetOwner()->GetActorForwardVector();
		}
		else
		{
			LeftOverDriftVelocity = Velocity;
			Velocity = 0.0f;
			Accelleration = 0.0f;
		}
	}
}