// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "HonkCarAsset.h"
#include "HonkWeaponAsset.h"
#include "HonkWeaponComponent.h"
#include "WorldPosition.h"


#include "HonkPawn.generated.h"

UCLASS()
class HONK_API AHonkPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AHonkPawn();
    // Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
    /** Movement Functions */
	void MoveForward(float Val);
	void MoveRight(float Val);

	/** Handbrake Functions */
	void OnHandbrakePressed();
	void OnHandbrakeReleased();

    /** Trigger Functions */
    void OnTriggerPressed();
    void OnTriggerReleased();
    void RotateWeapon();
    void GetAimUp(float val);
    void GetAimRight(float val);

	// Car data asset
	UPROPERTY()
	class UHonkCarAsset*	      CarAsset = nullptr;
	UPROPERTY(VisibleAnywhere)
	class USkeletalMeshComponent* CarMesh = nullptr;
	UPROPERTY()
	int32 CarTier = 0;

	// Weapon data asset
	UPROPERTY()
	class UHonkWeaponAsset* 	WeaponAsset = nullptr;
    UPROPERTY(VisibleAnywhere)
	class USkeletalMeshComponent* WeaponMesh = nullptr;

    UPROPERTY(VisibleAnywhere)
	class UBoxComponent* CollisionComponent = nullptr;

    UPROPERTY(EditDefaultsOnly)
    FName WeaponSocket = "WeaponSocket";

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	class UHonkMovementComponent* GetMovComp() { return MovComp; }

	UFUNCTION(BlueprintCallable)
	void SetWeapon(FName weapon, bool inConstructor = false);
	UFUNCTION(BlueprintCallable)
	void SetCar(FName car, int32 tier);
    UFUNCTION()
    void UpgradeCar();

	void DestroyAndRespawnPawn(float DeltaTime);
	void StartRespawn();
	bool Respawn = false;
	UPROPERTY(EditAnywhere)
	float RespawnDelay = 5;
	float CurrentDelay = 5;

	UPROPERTY(EditAnywhere)
	AWorldPosition* OffscreenPosition = nullptr;
	UPROPERTY(EditAnywhere)
	TArray<AWorldPosition*> SpawnPoints;

	int health;
	UPROPERTY(EditDefaultsOnly)
	int MaxHealthTier1 = 100;
	UPROPERTY(EditDefaultsOnly)
	int MaxHealthTier2 = 133;
	UPROPERTY(EditDefaultsOnly)
	int MaxHealthTier3 = 200;


private:
	// Scene positional components
    UPROPERTY(VisibleAnywhere)
    class USceneComponent* RootComp = nullptr;
	UPROPERTY(VisibleAnywhere)
    class USceneComponent* WeaponMount = nullptr;
	UPROPERTY(VisibleAnywhere)
    class USceneComponent* EndOfBarrel = nullptr;
	// Pawn logic components
	UPROPERTY(VisibleAnywhere)
	class UHonkMovementComponent* MovComp = nullptr;
	UPROPERTY(VisibleAnywhere)
    TSubclassOf<UHonkWeaponComponent> WeaponComp = nullptr;

	// Data assets
    UPROPERTY()
	UHonkWeaponComponent* WeaponInstance = nullptr;

	FName CarName;
	int   CurrentTier;

	/* Are we on a 'slippery' surface */
	bool bIsLowFriction;

    float XAxis = 0;
    float YAxis = 0;
};


