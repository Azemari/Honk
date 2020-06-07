// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HonkWeaponComponent.h"
#include "RocketLauncher.generated.h"

/**
 * 
 */
UCLASS()
class HONK_API URocketLauncher : public UHonkWeaponComponent
{
	GENERATED_BODY()
	
private:
	void Fire(float dTime) override;
	UFUNCTION()
	void Explosion(AHonkProjectile* projectile);

};
