// Fill out your copyright notice in the Description page of Project Settings.


#include "HonkProjectile.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

#include "HonkPawn.h"

// Sets default values
AHonkProjectile::AHonkProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<UStaticMeshComponent>("Root");
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>("ProjectileMesh");
	SetRootComponent(Root);
	ProjectileMesh->SetupAttachment(Root);
}

void AHonkProjectile::Initialise(UStaticMesh* mesh, float speed, float damage, FVector scale) 
{
	ProjectileMesh->SetStaticMesh(mesh);
	Speed = speed;
	Damage = damage;
	ProjectileMesh->SetRelativeScale3D(scale);
}

// Called when the game starts or when spawned
void AHonkProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

void AHonkProjectile::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if ((OtherActor != nullptr) && (OtherActor != this))
	{
		//stop when hitting walls
		if (ATyreWall* tyreWall = Cast<ATyreWall>(OtherActor))
		{
			Destroy();
		}
		else if(AArenaCollider* arena = Cast<AArenaCollider>(OtherActor))
		{
			Destroy();
		}
		//else if player, do damage
		else if (AHonkPawn* player = Cast<AHonkPawn>(OtherActor))
		{
			player->TakeDamage(Damage);
			Destroy();
		}
	}
}

// Called every frame
void AHonkProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector position = GetActorLocation();
	position += GetActorForwardVector() * Speed * DeltaTime;
	SetActorLocation(position);
}


