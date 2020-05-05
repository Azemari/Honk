// Fill out your copyright notice in the Description page of Project Settings.

#include "HonkPawn.h"
#include "HonkWeaponComponent.h"
#include "HonkMovementComponent.h"

#include "Components/SkeletalMeshComponent.h"
#include "Components/InputComponent.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
AHonkPawn::AHonkPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	MovComp = CreateDefaultSubobject<UHonkMovementComponent>(TEXT("MovementComp"));
	WeaponComp = CreateDefaultSubobject<UHonkWeaponComponent>(TEXT("WeaponComp"));

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(FName("Car Mesh"));
    RootComp->SetupAttachment(RootComponent);
	Mesh->SetupAttachment(RootComp);

    WeaponMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(FName("Weapon Mesh"));
    WeaponMeshComp->SetupAttachment(RootComp);

	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(FName("Collision Mesh"));
	CollisionComponent->SetupAttachment(RootComp);

}

// Called when the game starts or when spawned
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

void AHonkPawn::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{

}

// Called to bind functionality to input
void AHonkPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
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

// Called every frame
void AHonkPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}