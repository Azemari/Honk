// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Camera/CameraComponent.h"
#include "HonkPawn.h"
#include "EngineUtils.h"

#include "HonkCamera.generated.h"

UCLASS()
class HONK_API AHonkCamera : public AActor
{
	GENERATED_BODY()

    UPROPERTY(VisibleAnywhere)
    class USceneComponent* RootComp = nullptr;
    UPROPERTY(VisibleAnywhere)
    UCameraComponent* CameraComp = nullptr;
    
    UPROPERTY(VisibleAnywhere)
    int cameraMoveSpeed = 10;

    UPROPERTY(EditAnywhere)
    FVector CentroidOffset;
    UPROPERTY(EditAnywhere)
    float TargetSeparationThreshold;
    UPROPERTY(EditAnywhere)
    float MaxCameraZoom;
public:	
	// Sets default values for this actor's properties
	AHonkCamera();
    // Called every frame
	virtual void Tick(float DeltaTime) override;

    float FindLargestDistance(TArray<AActor*> AllPlayers);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
