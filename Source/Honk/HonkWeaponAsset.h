// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Components/StaticMeshComponent.h"

#include "HonkWeaponComponent.h"

#include "HonkWeaponAsset.generated.h"

USTRUCT(BlueprintType)
struct FWeaponData
{
    GENERATED_BODY()
	// Weapon Mechanical data
	UPROPERTY(EditAnywhere, Category=WeaponData)
	TSubclassOf<UHonkWeaponComponent> FiringMechanism;
	UPROPERTY(EditAnywhere, Category=WeaponStats)
	float RPM;
	UPROPERTY(EditAnywhere, Category=WeaponStats)
	float TurnRate;
	UPROPERTY(EditAnywhere, Category=WeaponStats)
	float ProjectileSpeed;
	UPROPERTY(EditAnywhere, Category=WeaponStats)
	float Damage;
	UPROPERTY(EditAnywhere, Category=WeaponStats)
	float Range;
	UPROPERTY(EditAnywhere, Category=WeaponStats)
	float ChargeSpeed;
	UPROPERTY(EditAnywhere, Category=WeaponStats)
	float ExplosionRange;
};

USTRUCT(BlueprintType)
struct FWeaponBlueprint
{
    GENERATED_BODY()

	// Weaopn mesh data
    UPROPERTY(EditAnywhere, Category=WeaponMeshes)
	UStaticMesh* WeaponBody = nullptr;
	UPROPERTY(EditAnywhere, Category=WeaponMeshes)
	UStaticMesh* WeaponBase = nullptr;
	UPROPERTY(EditAnywhere, Category=WeaponMeshes)
	UStaticMesh* WeaponGun = nullptr;
	UPROPERTY(EditAnywhere, Category=WeaponMeshes)
	UStaticMesh* WeaponBarrel = nullptr;

	// Weapon transform data
	UPROPERTY(EditAnywhere, Category=WeaponData)
	FVector EndOfBarrel;
	UPROPERTY(EditAnywhere, Category=WeaponData)
	FVector MeshRot;
	UPROPERTY(EditAnywhere, Category=WeaponData)
	FVector MeshScale;

	// Weapon Mechanical data
	UPROPERTY(EditAnywhere, Category=WeaponStats)
	FWeaponData WeaponStats;
};

UCLASS(BlueprintType)
class HONK_API UHonkWeaponAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TMap<FName, FWeaponBlueprint> Weapons;
};
