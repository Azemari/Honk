// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Components/StaticMeshComponent.h"



#include "ProjectileAsset.generated.h"
USTRUCT(BlueprintType)
struct FProjectileBlueprint
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category=ProjectileMeshes)
	UStaticMesh* ProjectileMesh = nullptr;
	UPROPERTY(EditAnywhere, Category=ProjectileMeshes)
	FVector Scale;



	UPROPERTY(EditAnywhere, Category=ProjectileData)
	float damage;
	UPROPERTY(EditAnywhere, Category=ProjectileData)
	float speed;
	UPROPERTY(EditAnywhere, Category=ProjectileData)
	float range;
	UPROPERTY(EditAnywhere, Category=ProjectileData)
	float ExplosionRange;
};

UCLASS()
class HONK_API UProjectileAsset : public UDataAsset
{
	GENERATED_BODY()

	public:
	UPROPERTY(EditAnywhere)
	TMap<FName, FProjectileBlueprint> Projectiles;
	
};
