// Fill out your copyright notice in the Description page of Project Settings.
#include "HonkWeaponDrop.h"

// Sets default values
AHonkWeaponDrop::AHonkWeaponDrop()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	DropMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DropMesh"));
	LightComponent = CreateDefaultSubobject<USpotLightComponent>(TEXT("LightComp"));
	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	Collider->SetCollisionProfileName("Trigger");

	RootComponent = DropMesh;
	LightComponent->SetupAttachment(RootComponent);
	Collider->SetupAttachment(RootComponent);

	Collider->OnComponentBeginOverlap.AddDynamic(this, &AHonkWeaponDrop::OnOverlapBegin);

	Weapons.Emplace(TEXT("MachineGun"));
	Weapons.Emplace(TEXT("RailGun"));
	Weapons.Emplace(TEXT("RocketLauncher"));
	Weapons.Emplace(TEXT("MiniGun"));
	Weapons.Emplace(TEXT("GrenadeLauncher"));

}

// Called when the game starts or when spawned
void AHonkWeaponDrop::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AHonkWeaponDrop::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	FRotator Rotator = FRotator(0, 180, 0);
	DropMesh->AddWorldRotation(Rotator * speed * DeltaTime);
}

void AHonkWeaponDrop::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) 
{
	if((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		if (AHonkPawn* other = Cast<AHonkPawn>(OtherActor))
		{
			other->SetWeapon(Weapons[FMath::RandRange(0,4)]);
		}
		Destroy();
	}
};