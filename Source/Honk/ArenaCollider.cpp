// Fill out your copyright notice in the Description page of Project Settings.

#include "ArenaCollider.h"

// Sets default values
AArenaCollider::AArenaCollider()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ArenaCollider1 = CreateDefaultSubobject<UBoxComponent>(TEXT("ArenaCollider1"));
	ArenaCollider2 = CreateDefaultSubobject<UBoxComponent>(TEXT("ArenaCollider2"));
	ArenaCollider3 = CreateDefaultSubobject<UBoxComponent>(TEXT("ArenaCollider3"));
	ArenaCollider4 = CreateDefaultSubobject<UBoxComponent>(TEXT("ArenaCollider4"));
	ArenaCollider5 = CreateDefaultSubobject<UBoxComponent>(TEXT("ArenaCollider5"));
	ArenaCollider6 = CreateDefaultSubobject<UBoxComponent>(TEXT("ArenaCollider6"));
	ArenaCollider7 = CreateDefaultSubobject<UBoxComponent>(TEXT("ArenaCollider7"));
	ArenaCollider8 = CreateDefaultSubobject<UBoxComponent>(TEXT("ArenaCollider8"));
	ArenaCollider9 = CreateDefaultSubobject<UBoxComponent>(TEXT("ArenaCollider9"));
	ArenaCollider10 = CreateDefaultSubobject<UBoxComponent>(TEXT("ArenaCollider10"));
	ArenaCollider11 = CreateDefaultSubobject<UBoxComponent>(TEXT("ArenaCollider11"));
	ArenaCollider12 = CreateDefaultSubobject<UBoxComponent>(TEXT("ArenaCollider12"));
}

// Called when the game starts or when spawned
void AArenaCollider::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AArenaCollider::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

