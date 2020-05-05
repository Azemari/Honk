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
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere, Category = AllWeapons)
    float rpm = 100;
    UPROPERTY(EditAnywhere, Category = AllWeapons)
    float damage = 10;
    UPROPERTY(EditAnywhere, Category = AllWeapons)
    float projectileSpeed = 10;

private:	
    void Fire(float dTime);

    float fireRate;
    float lastFired;
    bool  firing = false;
};
