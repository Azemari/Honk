// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "HonkPawn.h"
#include "Components/InputComponent.h"
#include "HonkMovementComponent.h"
#include "HonkWeaponComponent.h"
#include "Engine/SkeletalMesh.h"
#include "Engine/Engine.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/TextRenderComponent.h"
#include "Materials/Material.h"
#include "GameFramework/Controller.h"

#ifndef HMD_MODULE_INCLUDED
#define HMD_MODULE_INCLUDED 0
#endif

const FName AHonkPawn::LookUpBinding("LookUp");
const FName AHonkPawn::LookRightBinding("LookRight");

#define LOCTEXT_NAMESPACE "VehiclePawn"

void AHonkPawn::BeginPlay()
{
	Super::BeginPlay();
}

AHonkPawn::AHonkPawn(const FObjectInitializer& ObjectInitializer)
{
	WeaponComp = CreateDefaultSubobject<UHonkWeaponComponent>(TEXT("WeaponComp"));
	MovComp = CreateDefaultSubobject<UHonkMovementComponent>(TEXT("MovementComp"));

	//// Temp
	//static ConstructorHelpers::FObjectFinder<USkeletalMesh> CarMesh(TEXT("/Game/Vehicle/Sedan/Sedan_SkelMesh.Sedan_SkelMesh"));
	//Mesh = CarMesh.Object;

	/*static ConstructorHelpers::FClassFinder<UObject> AnimBPClass(TEXT("/Game/Vehicle/Sedan/Sedan_AnimBP"));
	GetMesh()->SetAnimInstanceClass(AnimBPClass.Class);*/
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
