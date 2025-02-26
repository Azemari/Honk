// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "TyreWall.generated.h"

UCLASS()
class HONK_API ATyreWall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATyreWall();
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* TyreMesh = nullptr;
	UPROPERTY(EditAnywhere)
	UBoxComponent* Collider = nullptr;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
