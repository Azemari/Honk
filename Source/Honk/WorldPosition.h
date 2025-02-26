// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SceneComponent.h"
#include "WorldPosition.generated.h"

UCLASS()
class HONK_API AWorldPosition : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWorldPosition();
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	USceneComponent* Position = nullptr;

	UFUNCTION()
	FVector GetPosition();
	UFUNCTION()
	FRotator GetRotation();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
