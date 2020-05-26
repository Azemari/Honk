// Fill out your copyright notice in the Description page of Project Settings.

#include "HonkCamera.h"
#include "Kismet/GameplayStatics.h"
//#include "Kismet/KismetMathLibrary.h"

// Sets default values
AHonkCamera::AHonkCamera()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
    RootComp->SetupAttachment(RootComponent);

    CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    CameraComp->SetupAttachment(RootComp);
}

// Called when the game starts or when spawned
void AHonkCamera::BeginPlay()
{
    UGameplayStatics::GetPlayerController(this, 0)->SetViewTarget(this);
	Super::BeginPlay();
	
}

// Called every frame
void AHonkCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

