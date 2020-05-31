// Fill out your copyright notice in the Description page of Project Settings.

#include "HonkPawn.h"
#include "HonkMovementComponent.h"

#include "Components/SkeletalMeshComponent.h"
#include "Components/InputComponent.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"

#include "ConstructorHelpers.h"
// Sets default values
AHonkPawn::AHonkPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Positional components
    RootComp 	= CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
    WeaponMount = CreateDefaultSubobject<USceneComponent>(TEXT("WeaponMount"));
    EndOfBarrel = CreateDefaultSubobject<USceneComponent>(TEXT("EndOfBarrel"));

	// Logic and Input Components
	MovComp = CreateDefaultSubobject<UHonkMovementComponent>(TEXT("MovementComp"));
	WeaponInstance = CreateDefaultSubobject<UHonkWeaponComponent>(TEXT("Weapon"));
	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Mesh"));

	// Setting up attachments
    RootComponent = RootComp;
	WeaponMount->SetupAttachment(RootComp);
	EndOfBarrel->SetupAttachment(WeaponMount);
	CollisionComponent->SetupAttachment(RootComp);

	// Loading inital car asset and meshes
	static ConstructorHelpers::FObjectFinder<UHonkCarAsset> CarData(TEXT("/Game/DataAssets/Cars"));
	CarAsset = CarData.Object;
	UE_LOG(LogTemp, Display, TEXT("CarAsset compile-time load: %s"), ((CarAsset != nullptr) ? TEXT("SUCCEEDED") : TEXT("FAILED")));

	CarMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Car Mesh"));
	CarMesh->SetupAttachment(RootComp);

	SetCar(TEXT("Camero"), 0);

	// Loading initial weapon asset and meshes (Machine gun)
	static ConstructorHelpers::FObjectFinder<UHonkWeaponAsset> WeaponData(TEXT("/Game/DataAssets/Weapons"));
	WeaponAsset = WeaponData.Object;
	UE_LOG(LogTemp, Display, TEXT("WeaponAsset compile-time load: %s"), ((WeaponAsset != nullptr) ? TEXT("SUCCEEDED") : TEXT("FAILED")));

    WeaponBodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponBody"));
    WeaponBodyMesh->SetupAttachment(WeaponMount);

	WeaponBaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponBase"));
    WeaponBaseMesh->SetupAttachment(WeaponMount);

	WeaponGunMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponGun"));
    WeaponGunMesh->SetupAttachment(WeaponMount);

	WeaponBarrelMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponBarrel"));
    WeaponBarrelMesh->SetupAttachment(WeaponMount);

	SetWeapon(TEXT("MachineGun"), true);
}

// Called when the game starts or when spawned
void AHonkPawn::BeginPlay()
{
	Super::BeginPlay();
	CollisionComponent->SetGenerateOverlapEvents(true);
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AHonkPawn::OnOverlapBegin);

	SetWeapon(TEXT("MachineGun"));
}

void AHonkPawn::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (MovComp)
	{
		if (AHonkPawn* OtherCar = Cast<AHonkPawn>(OtherActor))
		{
			MovComp->CollideWithCar(OtherCar, SweepResult);
		}
		else
		{
			MovComp->CollideWithWall(OtherActor, SweepResult);
		}
	}
}

// Called to bind functionality to input
void AHonkPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AHonkPawn::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AHonkPawn::MoveRight);
	PlayerInputComponent->BindAxis("LookUp");
	PlayerInputComponent->BindAxis("LookRight");

	PlayerInputComponent->BindAction("Handbrake", IE_Pressed, this, &AHonkPawn::OnHandbrakePressed);
	PlayerInputComponent->BindAction("Handbrake", IE_Released, this, &AHonkPawn::OnHandbrakeReleased);
    PlayerInputComponent->BindAction("Trigger", IE_Pressed, this, &AHonkPawn::OnTriggerPressed);
    PlayerInputComponent->BindAction("Trigger", IE_Released, this, &AHonkPawn::OnTriggerReleased);

}

void AHonkPawn::MoveForward(float Val)
{
    MovComp->SetThrottleInput(Val);
}

void AHonkPawn::MoveRight(float Val)
{
    MovComp->SetSteeringInput(Val);
}

void AHonkPawn::OnHandbrakePressed()
{
    MovComp->SetHandbrakeInput(true);
}

void AHonkPawn::OnHandbrakeReleased()
{
    MovComp->SetHandbrakeInput(false);
}

void AHonkPawn::OnTriggerPressed()
{
    WeaponInstance->SetTriggerStatus(true);
}

void AHonkPawn::OnTriggerReleased()
{
    WeaponInstance->SetTriggerStatus(false);
}

// Called every frame
void AHonkPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AHonkPawn::SetWeapon(FName weapon, bool inConstructor)
{
	if (WeaponAsset != nullptr)
	{
		if (WeaponAsset->Weapons.Contains(weapon))
		{
			EndOfBarrel->SetRelativeLocation(WeaponAsset->Weapons[weapon].EndOfBarrel);

            if (!inConstructor)
            {
			    WeaponComp = WeaponAsset->Weapons[weapon].WeaponStats.FiringMechanism;
			    WeaponInstance = NewObject<UHonkWeaponComponent>(this, WeaponComp, WeaponComp->GetFName());
				WeaponInstance->RegisterComponent();
                UE_LOG(LogTemp, Warning, TEXT("Weapon Instance: %s"), ((WeaponInstance != nullptr) ? TEXT("SUCCEEDED") : TEXT("FAILED")))
            }

			if (UStaticMesh* mesh = WeaponAsset->Weapons[weapon].WeaponBody)  
			{ 
				WeaponBodyMesh->SetStaticMesh(mesh);
				WeaponBodyMesh->SetRelativeScale3D(WeaponAsset->Weapons[weapon].MeshScale);
				WeaponBodyMesh->SetRelativeRotation(WeaponAsset->Weapons[weapon].MeshRot.Rotation().Quaternion());
			}
			if (UStaticMesh* mesh = WeaponAsset->Weapons[weapon].WeaponBase)  
			{
				WeaponBaseMesh->SetStaticMesh(mesh);  
				WeaponBaseMesh->SetRelativeScale3D(WeaponAsset->Weapons[weapon].MeshScale);
				WeaponBaseMesh->SetRelativeRotation(WeaponAsset->Weapons[weapon].MeshRot.Rotation().Quaternion());
			}
			if (UStaticMesh* mesh = WeaponAsset->Weapons[weapon].WeaponGun)   
			{
				WeaponGunMesh->SetStaticMesh(mesh);    
				WeaponGunMesh->SetRelativeScale3D(WeaponAsset->Weapons[weapon].MeshScale);   
				WeaponGunMesh->SetRelativeRotation(WeaponAsset->Weapons[weapon].MeshRot.Rotation().Quaternion());
			} 
			if (UStaticMesh* mesh = WeaponAsset->Weapons[weapon].WeaponBarrel)
			{
                WeaponBarrelMesh->SetVisibility(true);
				WeaponBarrelMesh->SetStaticMesh(mesh);
				WeaponBarrelMesh->SetRelativeScale3D(WeaponAsset->Weapons[weapon].MeshScale);
				WeaponBarrelMesh->SetRelativeRotation(WeaponAsset->Weapons[weapon].MeshRot.Rotation().Quaternion());
			}
            else
            {
                WeaponBarrelMesh->SetVisibility(false);
            }
		}
	}
}

void AHonkPawn::SetCar(FName car, int32 tier) 
{
	if (CarAsset != nullptr)
	{
		if (CarAsset->Cars.Contains(car))
		{
			switch (tier)
			{
			case 0:
				if (USkeletalMesh* mesh = CarAsset->Cars[car].Tier1Mesh)  
				{ 
					CarMesh->SetSkeletalMesh(mesh); 
					CarMesh->SetRelativeLocation(CarAsset->Cars[car].Tier1.MeshPos);
					CarMesh->SetRelativeRotation(CarAsset->Cars[car].Tier1.MeshRot.Rotation().Quaternion());

					CollisionComponent->SetRelativeLocation(CarAsset->Cars[car].Tier1.CollisionPos);
					CollisionComponent->SetRelativeScale3D(CarAsset->Cars[car].Tier1.CollisionScale);

					WeaponMount->SetRelativeLocation(CarAsset->Cars[car].Tier1.WeaponMountPos);
				}
				break;
			case 1:
				if (USkeletalMesh* mesh = CarAsset->Cars[car].Tier2Mesh)  
				{ 
					CarMesh->SetSkeletalMesh(mesh); 
					CarMesh->SetRelativeLocation(CarAsset->Cars[car].Tier2.MeshPos);
					CarMesh->SetRelativeRotation(CarAsset->Cars[car].Tier2.MeshRot.Rotation().Quaternion());

					CollisionComponent->SetRelativeLocation(CarAsset->Cars[car].Tier2.CollisionPos);
					CollisionComponent->SetRelativeScale3D(CarAsset->Cars[car].Tier2.CollisionScale);

					WeaponMount->SetRelativeLocation(CarAsset->Cars[car].Tier2.WeaponMountPos);
				}
				break;
			case 2:
				if (USkeletalMesh* mesh = CarAsset->Cars[car].Tier3Mesh)  
				{ 
					CarMesh->SetSkeletalMesh(mesh); 
					CarMesh->SetRelativeLocation(CarAsset->Cars[car].Tier3.MeshPos);
					CarMesh->SetRelativeRotation(CarAsset->Cars[car].Tier3.MeshRot.Rotation().Quaternion());

					CollisionComponent->SetRelativeLocation(CarAsset->Cars[car].Tier3.CollisionPos);
					CollisionComponent->SetRelativeScale3D(CarAsset->Cars[car].Tier3.CollisionScale);

					WeaponMount->SetRelativeLocation(CarAsset->Cars[car].Tier3.WeaponMountPos);
				}
				break;
			}
			
		}
	}
}