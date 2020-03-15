// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "HonkPawn.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/InputComponent.h"
#include "HonkMovementComponent.h"
#include "Engine/SkeletalMesh.h"
#include "Engine/Engine.h"
#include "Components/SceneComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/TextRenderComponent.h"
#include "Materials/Material.h"
#include "GameFramework/Controller.h"

#ifndef HMD_MODULE_INCLUDED
#define HMD_MODULE_INCLUDED 0
#endif

// Needed for VR Headset
#if HMD_MODULE_INCLUDED
#include "IXRTrackingSystem.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#endif // HMD_MODULE_INCLUDED

const FName AHonkPawn::LookUpBinding("LookUp");
const FName AHonkPawn::LookRightBinding("LookRight");

#define LOCTEXT_NAMESPACE "VehiclePawn"

AHonkPawn::AHonkPawn(const FObjectInitializer& ObjectInitializer)
{
	MovComp = CreateDefaultSubobject<UHonkMovementComponent>(TEXT("MovementComp"));

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(FName("Car Mesh"));
	Mesh->SetupAttachment(RootComponent);

	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(FName("Collision Mesh"));
	CollisionComponent->SetupAttachment(Mesh);
}

void AHonkPawn::BeginPlay()
{
	Super::BeginPlay();
	CollisionComponent->SetGenerateOverlapEvents(true);
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AHonkPawn::OnOverlapBegin);
}

void AHonkPawn::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (MovComp)
	{
		MovComp->CollideWithWall(OtherActor, SweepResult);
	}
}

void AHonkPawn::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AHonkPawn::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AHonkPawn::MoveRight);
	PlayerInputComponent->BindAxis("LookUp");
	PlayerInputComponent->BindAxis("LookRight");

	PlayerInputComponent->BindAction("Handbrake", IE_Pressed, this, &AHonkPawn::OnHandbrakePressed);
	PlayerInputComponent->BindAction("Handbrake", IE_Released, this, &AHonkPawn::OnHandbrakeReleased);
}

void AHonkPawn::MoveForward(float Val)
{
	MovComp->SetThrottleInput(Val);
}

void AHonkPawn::MoveRight(float Val)
{
	MovComp->SetSteeringInput(Val);
}

void AHonkPawn::OnHandbrakePressed()
{
	MovComp->SetHandbrakeInput(true);
}

void AHonkPawn::OnHandbrakeReleased()
{
	MovComp->SetHandbrakeInput(false);
}

void AHonkPawn::Tick(float Delta)
{
	Super::Tick(Delta);
	
}

#undef LOCTEXT_NAMESPACE
