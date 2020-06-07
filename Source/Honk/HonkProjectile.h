// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "TyreWall.h"
#include "ArenaCollider.h"

#include "HonkProjectile.generated.h"

UCLASS()
class HONK_API AHonkProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHonkProjectile();
	void Initialise(UStaticMesh* mesh, float speed, float damage, FVector scale);
	

	USceneComponent* Root;
	UPROPERTY(EditAnywhere, Category = "Components")
	class UStaticMeshComponent* ProjectileMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere)
	float Speed = 1;
	float Damage;
};
