// Fill out your copyright notice in the Description page of Project Settings.


#include "RailGun.h"


void URailGun::Fire(float dTime) 
{
    if (Firing && LastFired <= 0.0f)
    {
        FActorSpawnParameters spawnParams;
        AHonkProjectile* projectile = GetWorld()->SpawnActor<AHonkProjectile>(AHonkProjectile::StaticClass(),
                         Barrel->GetComponentLocation(),
                         Barrel->GetComponentRotation(),
                         spawnParams);
        projectile->Initialise(ProjectileBP.ProjectileMesh, ProjectileBP.speed, ProjectileBP.damage, ProjectileBP.Scale);
        projectile->ProjectileMesh->SetRelativeRotation(FRotator(0, -90, 0));

        Bursting = true;
        BurstFired++;
        LastBurst = BurstRate;
        LastFired = FireRate;
    }

    if (Bursting && LastBurst <= 0.0f && BurstFired <= 2)
    {
        FActorSpawnParameters spawnParams;
        AHonkProjectile* projectile = GetWorld()->SpawnActor<AHonkProjectile>(AHonkProjectile::StaticClass(),
                         Barrel->GetComponentLocation(),
                         Barrel->GetComponentRotation(),
                         spawnParams);
        projectile->Initialise(ProjectileBP.ProjectileMesh, ProjectileBP.speed, ProjectileBP.damage, ProjectileBP.Scale);
        projectile->ProjectileMesh->SetRelativeRotation(FRotator(0, -90, 0));

        BurstFired++;
        LastBurst = BurstRate;
    }

    if (LastFired > 0.0f)
    {
        LastBurst -= dTime;
        LastFired -= dTime;
    }

    if (BurstFired == 3)
    {
        BurstFired = 0;
        Bursting = false;
    }
}
