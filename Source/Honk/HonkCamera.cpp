// Fill out your copyright notice in the Description page of Project Settings.

#include "HonkCamera.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

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
	Super::BeginPlay();
    UGameplayStatics::GetPlayerController(this, 0)->SetViewTarget(this);

    for(TActorIterator<AHonkPawn> ActorIterator(GetWorld()); ActorIterator; ++ActorIterator)
    {
        Players.Add(*ActorIterator);
    }
}

// Called every frame
void AHonkCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if(UGameplayStatics::GetPlayerController(this, 0)->GetViewTarget() != this)
    {
        UGameplayStatics::GetPlayerController(this, 0)->SetViewTarget(this);
    }

    if (Players.Num() > 0)
    {
     //// Move camera to be above centroid of Players
     //FVector centroid = UGameplayStatics::GetActorArrayAverageLocation(Players);
     //FVector location = centroid + CentroidOffset;
     //FRotator lookAt = UKismetMathLibrary::FindLookAtRotation(location, centroid);
     //SetActorLocationAndRotation(location, lookAt);

     //// Zoom out based on target separation
     //float maxDist = MaxDistanceBetweenTargets();
     //float zoom = UKismetMathLibrary::FClamp((maxDist - TargetSeparationThreshold), 0.0f, MaxCameraZoom);
     //CameraComp->SetRelativeLocation(FVector(zoom * -1.0f, 0.0f, 0.0f));
    }

}

