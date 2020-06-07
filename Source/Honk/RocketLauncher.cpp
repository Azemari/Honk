// Fill out your copyright notice in the Description page of Project Settings.


#include "RocketLauncher.h"


void URocketLauncher::Fire(float dTime) 
{
       if (Firing && LastFired <= 0.0f)
    {
        FActorSpawnParameters spawnParams;
	    AHonkProjectile* projectile = GetWorld()->SpawnActor<AHonkProjectile>(AHonkProjectile::StaticClass(),
	    				 Barrel->GetComponentLocation(),
	    				 Barrel->GetComponentRotation(),
                         spawnParams);
        projectile->Initialise(ProjectileBP.ProjectileMesh, ProjectileBP.speed, 0, ProjectileBP.Scale);
        projectile->ProjectileMesh->SetRelativeRotation(FRotator(0,-90,0));

        projectile->OnDetonate.AddDynamic(this, &URocketLauncher::Explosion);

        LastFired = FireRate;
    }

    if(LastFired > 0.0f)
    {
        LastFired -= dTime;
    }
}

void URocketLauncher::Explosion(AHonkProjectile* projectile) 
{
    //if we can explode
    if (ProjectileBP.ExplosionClass != nullptr)
    {
        //explode
        FActorSpawnParameters spawnParams;
        AHonkExplosion* explosion = GetWorld()->SpawnActor<AHonkExplosion>(ProjectileBP.ExplosionClass,
	    				 projectile->GetActorLocation(),
	    				 projectile->GetActorRotation(),
                         spawnParams);

        explosion->Initialise(ProjectileBP.ExplosionRange, ProjectileBP.damage);
    }
}
