// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/SkeletalMesh.h"

#include "HonkWeaponComponent.generated.h"

UCLASS( ClassGroup=(Custom), blueprintable, meta=(BlueprintSpawnableComponent) )
class HONK_API UHonkWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHonkWeaponComponent();
	~UHonkWeaponComponent();
	// Called when the game starts
	virtual void BeginPlay() override;
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	USkeletalMeshComponent* GetMesh() { return weaponMesh; }

protected:
	UPROPERTY(EditAnywhere, Category = "WeaponStats")
	float fireRate = 10;
	UPROPERTY(EditAnywhere, Category = "WeaponStats")
	float aiminngAngle = 360;
	UPROPERTY(EditAnywhere, Category = "WeaponStats")
	float damage = 1;
	UPROPERTY(EditAnywhere, Category = "WeaponStats")
	float range = 10;
	UPROPERTY(EditAnywhere, Category = "WeaponStats")
	float projectileSpeed = 10;
	UPROPERTY(EditAnywhere, Category = "WeaponStats", meta = (ClampMin = 0, ClampMax = 2))
	int heightRange = 1;

	UPROPERTY(EditAnywhere, Category = "Railgun, Magnet and Whip")
	float chargeRate = 1;
	UPROPERTY(EditAnywhere, Category = "ChainSaw")
	float slowRate = 0.5;
	UPROPERTY(EditAnywhere, Category = "Explosives")
	float fallOff;

	USkeletalMeshComponent* weaponMesh = nullptr;

private:
	float lastFired;

		
};
