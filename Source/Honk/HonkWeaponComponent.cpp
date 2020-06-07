// Fill out your copyright notice in the Description page of Project Settings.
#include "HonkWeaponComponent.h"
#include "ConstructorHelpers.h"


// Sets default values for this component's properties
UHonkWeaponComponent::UHonkWeaponComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

    //Loading projectile asset
    static ConstructorHelpers::FObjectFinder<UProjectileAsset> ProjectileData(TEXT("/Game/DataAssets/Projectiles"));
	ProjectileAsset = ProjectileData.Object;
	UE_LOG(LogTemp, Display, TEXT("ProjectileAsset compile-time load: %s"), ((ProjectileAsset != nullptr) ? TEXT("SUCCEEDED") : TEXT("FAILED")));
}

void UHonkWeaponComponent::Initialise(USceneComponent* EndOfBarrel, FName projectileName)
{
    Barrel = EndOfBarrel;
    if (ProjectileAsset != nullptr)
    {
        if (ProjectileAsset->Projectiles.Contains(projectileName))
        {
            ProjectileBP = ProjectileAsset->Projectiles[projectileName];
        }
    }
}

// Called when the game starts
void UHonkWeaponComponent::BeginPlay()
{
	Super::BeginPlay();	

    MaxFireRate = 1/(MaxRPM/60);
    FireRate = 1/(RPM/60);
    LastFired = 0.0f;
    Firing = false;
}

// Called every frame
void UHonkWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    Fire(DeltaTime);
}

void UHonkWeaponComponent::SetTriggerStatus(bool status)
{
    Firing = status;
}

void UHonkWeaponComponent::Fire(float dTime)
{
    if (Firing && LastFired <= 0.0f)
    {
        UE_LOG(LogTemp, Warning, TEXT("This function needs overriding"));
        LastFired = FireRate;
    }

    if(LastFired > 0.0f)
    {
        LastFired -= dTime;
    }
}

