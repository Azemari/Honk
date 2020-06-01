// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Components/SkeletalMeshComponent.h"
#include "HonkCarAsset.generated.h"

USTRUCT(BlueprintType)
struct FTierData
{
	GENERATED_BODY()

	// Tier 1 info
	UPROPERTY(EditAnywhere, Category=CarData)
	FVector MeshPos;
	UPROPERTY(EditAnywhere, Category=CarData)
	FVector MeshRot;
	UPROPERTY(EditAnywhere, Category=CarData)
	FVector WeaponMountPos;
	UPROPERTY(EditAnywhere, Category=CarData)
	FVector CollisionPos;
	UPROPERTY(EditAnywhere, Category=CarData)
	FVector CollisionScale;
};

USTRUCT(BlueprintType)
struct FCarBlueprint
{
	GENERATED_BODY()

	// Meshes
	UPROPERTY(EditAnywhere, Category=CarMeshes)
	USkeletalMesh* Tier1Mesh = nullptr;
	UPROPERTY(EditAnywhere, Category=CarMeshes)
	USkeletalMesh* Tier2Mesh = nullptr;
	UPROPERTY(EditAnywhere, Category=CarMeshes)
	USkeletalMesh* Tier3Mesh = nullptr;

	// Tier 1 info
	UPROPERTY(EditAnywhere, Category=CarData)
	FTierData Tier1;
	UPROPERTY(EditAnywhere, Category=CarData)
	FTierData Tier2;
	UPROPERTY(EditAnywhere, Category=CarData)
	FTierData Tier3;

};

UCLASS(BlueprintType)
class HONK_API UHonkCarAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	TMap<FName, FCarBlueprint> Cars;
};
