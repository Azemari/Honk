// Fill out your copyright notice in the Description page of Project Settings.

#include "ArenaCollider.h"

// Sets default values
AArenaCollider::AArenaCollider()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComp 	   = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	RootComponent  = RootComp;
	ArenaCollider1 = CreateDefaultSubobject<UBoxComponent>(TEXT("ArenaCollider1"));
	ArenaCollider1->SetupAttachment(RootComp);
	ArenaCollider2 = CreateDefaultSubobject<UBoxComponent>(TEXT("ArenaCollider2"));
	ArenaCollider2->SetupAttachment(RootComp);
	ArenaCollider3 = CreateDefaultSubobject<UBoxComponent>(TEXT("ArenaCollider3"));
	ArenaCollider3->SetupAttachment(RootComp);
	ArenaCollider4 = CreateDefaultSubobject<UBoxComponent>(TEXT("ArenaCollider4"));
	ArenaCollider4->SetupAttachment(RootComp);
	ArenaCollider5 = CreateDefaultSubobject<UBoxComponent>(TEXT("ArenaCollider5"));
	ArenaCollider5->SetupAttachment(RootComp);
	ArenaCollider6 = CreateDefaultSubobject<UBoxComponent>(TEXT("ArenaCollider6"));
	ArenaCollider6->SetupAttachment(RootComp);
	ArenaCollider7 = CreateDefaultSubobject<UBoxComponent>(TEXT("ArenaCollider7"));
	ArenaCollider7->SetupAttachment(RootComp);
	ArenaCollider8 = CreateDefaultSubobject<UBoxComponent>(TEXT("ArenaCollider8"));
	ArenaCollider8->SetupAttachment(RootComp);
	ArenaCollider9 = CreateDefaultSubobject<UBoxComponent>(TEXT("ArenaCollider9"));
	ArenaCollider9->SetupAttachment(RootComp);
	ArenaCollider10 = CreateDefaultSubobject<UBoxComponent>(TEXT("ArenaCollider10"));
	ArenaCollider10->SetupAttachment(RootComp);
	ArenaCollider11 = CreateDefaultSubobject<UBoxComponent>(TEXT("ArenaCollider11"));
	ArenaCollider11->SetupAttachment(RootComp);
	ArenaCollider12 = CreateDefaultSubobject<UBoxComponent>(TEXT("ArenaCollider12"));
	ArenaCollider12->SetupAttachment(RootComp);
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

