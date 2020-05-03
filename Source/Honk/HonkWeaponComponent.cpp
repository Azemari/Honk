// Fill out your copyright notice in the Description page of Project Settings.


#include "HonkWeaponComponent.h"

// Sets default values for this component's properties
UHonkWeaponComponent::UHonkWeaponComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

    fireRate = 1/(rpm/60);
    lastFired = fireRate;
	// ...
}


// Called when the game starts
void UHonkWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Called every frame
void UHonkWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    Fire(DeltaTime);

	// ...
}

void UHonkWeaponComponent::SetTriggerStatus(bool status)
{
    firing = status;
}

void UHonkWeaponComponent::Fire(float dTime)
{
    if (firing && lastFired < 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("Fired") );
        lastFired = fireRate;
    }
    
    lastFired -= (rpm/60);
}

