// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HonkProjectile.h"
#include "ProjectileAsset.h"

#include "HonkWeaponComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HONK_API UHonkWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHonkWeaponComponent();
    void Initialise(USceneComponent* EndOfBarrel, FName projectileName);
    // Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    void SetTriggerStatus(bool status);

    void SetMaxRPM(float newMaxRPM) {MaxRPM = newMaxRPM; MaxFireRate = 1/(MaxRPM/60); }
    void SetRPM(float newRPM) { RPM = newRPM; FireRate = 1/(RPM/60); }
    void SetTurnRate(float newTurnRate) { TurnRate = newTurnRate; }
    void SetChargeSpeed(float newChargeSpeed) { ChargeSpeed = newChargeSpeed; }

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

    UPROPERTY()
    class UProjectileAsset* ProjectileAsset = nullptr;

    // Manage the fire rate
    float MaxFireRate;
    float FireRate;
    float LastFired;
    UPROPERTY()
    bool  Firing;

    // Weapon stats, set in the Weapons data asset
    float MaxRPM;
	float RPM;
	float TurnRate;
	float ChargeSpeed;

    UPROPERTY()
    USceneComponent* Barrel = nullptr;
    UPROPERTY()
    FProjectileBlueprint ProjectileBP;

private:	
    virtual void Fire(float dTime);
};
