// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HonkWeaponComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HONK_API UHonkWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHonkWeaponComponent();
    // Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    void SetTriggerStatus(bool status);

    void SetRPM(float newRPM);
    void SetTrunRate(float newTurnRate);
    void SetProjectileSpeed(float newProjectileSpeed);
    void SetDamage(float newDamage);
    void SetRange(float newRange);
    void SetChargeSpeed(float newChargeSpeed);
    void SetExplosionRange(float newExplosionRange);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

    // Manage the fire rate
    float FireRate;
    float LastFired;
    UPROPERTY()
    bool  Firing;

    // Weapon stats, set in the Weapons data asset
	float RPM = 1;
	float TurnRate;
	float ProjectileSpeed;
	float Damage;
	float Range;
	float ChargeSpeed;
	float ExplosionRange;
private:	
    void Fire(float dTime);
    int count = 0;
};
