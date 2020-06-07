// Fill out your copyright notice in the Description page of Project Settings.


#include "HonkExplosion.h"

#include "HonkPawn.h"

// Sets default values
AHonkExplosion::AHonkExplosion()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AHonkExplosion::BeginPlay()
{
	Super::BeginPlay();
	
}

void AHonkExplosion::NotifyActorBeginOverlap(AActor* OtherActor) 
{
	if ((OtherActor != nullptr) && (OtherActor != this))
	{
		//if player, do damage
		if (AHonkPawn* player = Cast<AHonkPawn>(OtherActor))
		{
			player->TakeDamage(Damage);
		}
	}
}

// Called every frame
void AHonkExplosion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHonkExplosion::Initialise(float radius, float damage) 
{
	Radius = radius;
	Damage = damage;
	OnExplode();
}

