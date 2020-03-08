// Fill out your copyright notice in the Description page of Project Settings.


#include "HonkWeaponComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/SkeletalMesh.h"
#include "Engine/Engine.h"
#include "UObject/ConstructorHelpers.h"
#include "Materials/Material.h"

// Sets default values for this component's properties
UHonkWeaponComponent::UHonkWeaponComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	weaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	static ConstructorHelpers::FObjectFinder<USkeletalMeshComponent> mesh(TEXT("/Game/Shape_Cube"));
	weaponMesh = mesh.Object;
}

UHonkWeaponComponent::~UHonkWeaponComponent()
{
	delete weaponMesh;
	weaponMesh = nullptr;
}

// Called when the game starts
void UHonkWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
	

	// ...
	
}

void Fire()
{
    checkf(false, TEXT("Overload fire function in child, ya goon"));
}


// Called every frame
void UHonkWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

