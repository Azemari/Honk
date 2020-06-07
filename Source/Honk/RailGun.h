// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HonkWeaponComponent.h"
#include "RailGun.generated.h"

/**
 * 
 */
UCLASS()
class HONK_API URailGun : public UHonkWeaponComponent
{
	GENERATED_BODY()
	
private:
	bool Bursting = false;
	float BurstRate = 0.1f;
	float LastBurst = 0.0f;
	int BurstFired = 0;

	void Fire(float dTime) override;
};
