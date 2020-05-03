// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "HonkPawn.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/InputComponent.h"
#include "HonkMovementComponent.h"
#include "HonkWeaponComponent.h"
#include "Engine/SkeletalMesh.h"
#include "Engine/Engine.h"
#include "Components/SceneComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/TextRenderComponent.h"
#include "Materials/Material.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Controller.h"

#define LOCTEXT_NAMESPACE "VehiclePawn"

AHonkPawn::AHonkPawn(const FObjectInitializer& ObjectInitializer)
{
	MovComp = CreateDefaultSubobject<UHonkMovementComponent>(TEXT("MovementComp"));
	WeaponComp = CreateDefaultSubobject<UHonkWeaponComponent>(TEXT("WeaponComp"));

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(FName("Car Mesh"));
	Mesh->SetupAttachment(RootComponent);

    WeaponMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(FName("Weapon Mesh"));
    WeaponMeshComp->SetupAttachment(Mesh, WeaponSocket);

	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(FName("Collision Mesh"));
	CollisionComponent->SetupAttachment(Mesh);
}

void AHonkPawn::BeginPlay()
{
	Super::BeginPlay();    
  
    if(WeaponMeshComp)
    {
        if (WeaponMeshBase.IsPending())
        {
            WeaponMeshBase.LoadSynchronous();
        }
        WeaponMeshComp->SetSkeletalMesh(WeaponMeshBase.Get());
    }

	CollisionComponent->SetGenerateOverlapEvents(true);
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AHonkPawn::OnOverlapBegin);
}

void AHonkPawn::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (MovComp)
	{
		if (AHonkPawn* OtherCar = Cast<AHonkPawn>(OtherActor))
		{
			MovComp->CollideWithCar(OtherCar, SweepResult);
		}
		else
		{
			MovComp->CollideWithWall(OtherActor, SweepResult);
		}
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
    PlayerInputComponent->BindAction("Trigger", IE_Pressed, this, &AHonkPawn::OnTriggerPressed);
    PlayerInputComponent->BindAction("Trigger", IE_Released, this, &AHonkPawn::OnTriggerReleased);
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

void AHonkPawn::OnTriggerPressed()
{
    WeaponComp->SetTriggerStatus(true);
}

void AHonkPawn::OnTriggerReleased()
{
    WeaponComp->SetTriggerStatus(false);
}

void AHonkPawn::Tick(float Delta)
{
	Super::Tick(Delta);
}

#undef LOCTEXT_NAMESPACE
