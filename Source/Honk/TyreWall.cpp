// Fill out your copyright notice in the Description page of Project Settings.


#include "TyreWall.h"

// Sets default values
ATyreWall::ATyreWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	TyreMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TyreMesh"));
	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));

	RootComponent = TyreMesh;
	Collider->SetupAttachment(TyreMesh);
}

// Called when the game starts or when spawned
void ATyreWall::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATyreWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

