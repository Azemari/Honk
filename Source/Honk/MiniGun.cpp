// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniGun.h"


void UMiniGun::Fire(float dTime)
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
        
        //Accelerate fire rate
        if (FireRate >= (1/(MaxRPM/60)))
        {
           FireRate -= (3.0f * dTime);

           if (FireRate < (1/(MaxRPM/60)))
           {
               FireRate = 1/(MaxRPM/60);
           }
        }

        UE_LOG(LogTemp, Warning, TEXT("+Fire rate = %f"), FireRate);
        LastFired = FireRate;
    }
    //Decelerate fire rate
    else if (!Firing && FireRate < (1/(RPM/60)))
    {
        FireRate += (0.5f * dTime);
        UE_LOG(LogTemp, Warning, TEXT("-Fire rate = %f"), FireRate);
    }

    if(LastFired > 0.0f)
    {
        LastFired -= dTime;
    }
}