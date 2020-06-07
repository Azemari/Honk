// Fill out your copyright notice in the Description page of Project Settings.

#include "HonkPawn.h"
#include "HonkMovementComponent.h"
#include "HonkWeaponComponent.h"

#include "Components/SkeletalMeshComponent.h"
#include "Components/InputComponent.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/PlayerController.h"
#include "HonkGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "UnrealMathUtility.h"
#include "UnrealMathVectorConstants.h"

#include "ConstructorHelpers.h"

// Sets default values
AHonkPawn::AHonkPawn()
{

	health = MaxHealthTier1;

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

	//CarName = TEXT("Camero");
	//SetCar(CarName, 0);

	// Loading initial weapon asset and meshes (Machine gun)
	static ConstructorHelpers::FObjectFinder<UHonkWeaponAsset> WeaponData(TEXT("/Game/DataAssets/Weapons"));
	WeaponAsset = WeaponData.Object;
	UE_LOG(LogTemp, Display, TEXT("WeaponAsset compile-time load: %s"), ((WeaponAsset != nullptr) ? TEXT("SUCCEEDED") : TEXT("FAILED")));

    WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
    WeaponMesh->SetupAttachment(WeaponMount);;

	SetWeapon(TEXT("MachineGun"), true);
}

// Called when the game starts or when spawned
void AHonkPawn::BeginPlay()
{
	Super::BeginPlay();
	CollisionComponent->SetGenerateOverlapEvents(true);
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AHonkPawn::OnOverlapBegin);

	if (UHonkGameInstance* GI = Cast<UHonkGameInstance>(GetGameInstance()))
	{
		FString CarString = GI->GetPlayerCar(UGameplayStatics::GetPlayerControllerID(Cast<APlayerController>(GetController())));
		CarName = FName(*CarString);
		SetCar(CarName, 0);
	}

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
    PlayerInputComponent->BindAxis("AimUp", this, &AHonkPawn::GetAimUp);
    PlayerInputComponent->BindAxis("AimRight", this, &AHonkPawn::GetAimRight);

	PlayerInputComponent->BindAction("Handbrake", IE_Pressed, this, &AHonkPawn::OnHandbrakePressed);
	PlayerInputComponent->BindAction("Handbrake", IE_Released, this, &AHonkPawn::OnHandbrakeReleased);
    PlayerInputComponent->BindAction("Trigger", IE_Pressed, this, &AHonkPawn::OnTriggerPressed);
    PlayerInputComponent->BindAction("Trigger", IE_Released, this, &AHonkPawn::OnTriggerReleased);
	PlayerInputComponent->BindAction("Respawn", IE_Pressed, this, &AHonkPawn::StartRespawn);
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



void AHonkPawn::GetAimUp(float val)
{
    YAxis = val;
}
void AHonkPawn::GetAimRight(float val)
{
    XAxis = val;
}

void AHonkPawn::RotateWeapon()
{
    if ((YAxis != 0.0f) || (XAxis != 0.0f))
    {
        FRotator rotation;
        if ((YAxis == 1 || YAxis == -1) && (XAxis == 1 || XAxis == -1))
        {
            float forward = ((YAxis >= 0.0f) ? 0.0f : 180.0f);
            float right = (90.0f * XAxis) * ((YAxis >= 0.0f) ? 1.0f : -1.0f);

            float angle = ((forward + right) - ((right > 0) ? 45:-45));

            rotation = FRotator(0.0f, angle, 0.0f);
            WeaponMount->SetWorldRotation(rotation);
        }
        else
        {
            float forward = ((YAxis >= 0.0f) ? 0.0f : 180.0f);
            float right = (90.0f * XAxis) * ((YAxis >= 0.0f) ? 1.0f : -1.0f);
            rotation = FRotator(0.0f, forward + right, 0.0f);
            WeaponMount->SetWorldRotation(rotation);
        }
    }
    else
    {
        WeaponMount->SetRelativeRotation(FRotator::ZeroRotator);
    }
}

// Called every frame
void AHonkPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    RotateWeapon();

	if (health < 0){ StartRespawn(); }
	if (Respawn){ DestroyAndRespawnPawn(DeltaTime); }
}

void AHonkPawn::SetWeapon(FName weapon, bool inConstructor)
{
	if (WeaponAsset != nullptr)
	{
		if (WeaponAsset->Weapons.Contains(weapon))
		{
			//EndOfBarrel->SetRelativeLocation(FVector(0,0,0));
			EndOfBarrel->SetRelativeLocation(WeaponAsset->Weapons[weapon].EndOfBarrel);

            if (!inConstructor)
            {
			    TSubclassOf<UHonkWeaponComponent> weaponComp = WeaponAsset->Weapons[weapon].WeaponStats.FiringMechanism;
			    WeaponInstance = NewObject<UHonkWeaponComponent>(this, weaponComp, weaponComp->GetFName());
				WeaponInstance->RegisterComponent();
				WeaponInstance->Initialise(EndOfBarrel, WeaponAsset->Weapons[weapon].ProjectileName);
				WeaponInstance->SetRPM(WeaponAsset->Weapons[weapon].WeaponStats.RPM);
				WeaponInstance->SetChargeSpeed(WeaponAsset->Weapons[weapon].WeaponStats.ChargeSpeed);
                UE_LOG(LogTemp, Warning, TEXT("Weapon Instance: %s"), ((WeaponInstance != nullptr) ? TEXT("SUCCEEDED") : TEXT("FAILED")))
			}
			if (USkeletalMesh* mesh = WeaponAsset->Weapons[weapon].WeaponMesh)  
			{ 
				WeaponMesh->SetSkeletalMesh(mesh);
				WeaponMesh->SetRelativeScale3D(WeaponAsset->Weapons[weapon].MeshScale);
				WeaponMesh->SetRelativeRotation(WeaponAsset->Weapons[weapon].MeshRot.Rotation().Quaternion());
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

void AHonkPawn::UpgradeCar() 
{
	if (CarAsset != nullptr)
	{
		if (CurrentTier < 2)
		{
			++CurrentTier;
			switch (CurrentTier)
			{
			case 1:
				if (USkeletalMesh* mesh = CarAsset->Cars[CarName].Tier2Mesh)  
				{ 
					CarMesh->SetSkeletalMesh(mesh); 
					CarMesh->SetRelativeLocation(CarAsset->Cars[CarName].Tier2.MeshPos);
					CarMesh->SetRelativeRotation(CarAsset->Cars[CarName].Tier2.MeshRot.Rotation().Quaternion());

					CollisionComponent->SetRelativeLocation(CarAsset->Cars[CarName].Tier2.CollisionPos);
					CollisionComponent->SetRelativeScale3D(CarAsset->Cars[CarName].Tier2.CollisionScale);

					WeaponMount->SetRelativeLocation(CarAsset->Cars[CarName].Tier2.WeaponMountPos);
					health = MaxHealthTier2;
				}
				break;
			case 2:
				if (USkeletalMesh* mesh = CarAsset->Cars[CarName].Tier3Mesh)  
				{ 
					CarMesh->SetSkeletalMesh(mesh); 
					CarMesh->SetRelativeLocation(CarAsset->Cars[CarName].Tier3.MeshPos);
					CarMesh->SetRelativeRotation(CarAsset->Cars[CarName].Tier3.MeshRot.Rotation().Quaternion());

					CollisionComponent->SetRelativeLocation(CarAsset->Cars[CarName].Tier3.CollisionPos);
					CollisionComponent->SetRelativeScale3D(CarAsset->Cars[CarName].Tier3.CollisionScale);

					WeaponMount->SetRelativeLocation(CarAsset->Cars[CarName].Tier3.WeaponMountPos);
					health = MaxHealthTier3;
				}
				break;
			}
		}
		else
		{
			health = MaxHealthTier3;
		}
		
	}
}

void AHonkPawn::DestroyAndRespawnPawn(float DeltaTime) 
{
	this->SetActorLocation(FVector(5000,5000,5000));
	//this->SetActorLocation(OffscreenPosition->GetPosition());

	SetCar(CarName, 0);
	SetWeapon(TEXT("MachineGun"));
	CurrentTier = 0;
	health = MaxHealthTier1;

	if (CurrentDelay < 0)
	{
		int32 index = FMath::RandRange(0, SpawnPoints.Num()-1);
		this->SetActorLocation(FVector(700,-1400,-4));
		//this->SetActorLocation(SpawnPoints[index]->GetPosition());
		//this->SetActorRotation(SpawnPoints[index]->GetRotation());

		CurrentDelay = RespawnDelay;
		Respawn = false;
	}
	else
	{
		CurrentDelay -= DeltaTime;
	}
}

void AHonkPawn::StartRespawn() 
{
	Respawn = true;
}