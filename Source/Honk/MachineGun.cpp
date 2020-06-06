// Fill out your copyright notice in the Description page of Project Settings.


#include "MachineGun.h"


void UMachineGun::Fire(float dTime) 
{
    if (Firing && LastFired <= 0.0f)
    {
        FActorSpawnParameters spawnParams;
	    AHonkProjectile* projectile = GetWorld()->SpawnActor<AHonkProjectile>(AHonkProjectile::StaticClass(),
	    				 Barrel->GetComponentLocation(),
	    				 Barrel->GetComponentRotation(),
                         spawnParams);
        projectile->Initialise(ProjectileBP.ProjectileMesh, ProjectileBP.speed, ProjectileBP.Scale);
        projectile->ProjectileMesh->SetRelativeRotation(FRotator(0,-90,0));
        LastFired = FireRate;
    }

    if(LastFired > 0.0f)
    {
        LastFired -= dTime;
    }
}
