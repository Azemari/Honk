// Fill out your copyright notice in the Description page of Project Settings.

#include "HonkCamera.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

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

    
}

// Called every frame
void AHonkCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


    TArray<AActor*> Players;
    TArray<AActor*> CastedPlayers;
    UGameplayStatics::GetAllActorsOfClass(this, AHonkPawn::StaticClass(), Players);

    for (const auto& player: Players)
    {
        if (AHonkPawn* pawn = Cast<AHonkPawn>(player))
        {
            if(!pawn->RespawnStatus())
            {
                CastedPlayers.Add(pawn);
            }
        }
    }


    if(UGameplayStatics::GetPlayerController(this, 0)->GetViewTarget() != this)
    {
        UGameplayStatics::GetPlayerController(this, 0)->SetViewTarget(this);
    }

    if (Players.Num() > 0)
    {
        //// Move camera to be above centroid of Players
        FVector centroid = UGameplayStatics::GetActorArrayAverageLocation(CastedPlayers);
        FVector location = centroid + CentroidOffset;
        FRotator lookAt = UKismetMathLibrary::FindLookAtRotation(location, centroid);
        SetActorLocationAndRotation(location, lookAt);       
        UKismetSystemLibrary::DrawDebugFrustum(this, FTransform(centroid + FVector(0,0,20)), FLinearColor::Green, 0.001f, 50);
        // Zoom out based on target separation
        float maxDist = FindLargestDistance(CastedPlayers);
        float zoom = UKismetMathLibrary::FClamp((maxDist - TargetSeparationThreshold), 0.0f, MaxCameraZoom);
        CameraComp->SetRelativeLocation(FVector(zoom * -1.0f, 0.0f, 0.0f));
    }

}

float AHonkCamera::FindLargestDistance(TArray<AActor*> Players) 
{
    float maxDistance = 0;
    for (int i = 0; i < Players.Num() - 1; ++i)
    {
        for (int j = i + 1; j < Players.Num(); ++j)
        {
            float dist = FVector::Dist(Players[i]->GetActorLocation(), Players[j]->GetActorLocation());
            if (dist > maxDistance)
            {
                maxDistance = dist;
            }
        }
    }
    return maxDistance;
}

