// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
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

    UPROPERTY(VisibleAnywhere)
	class USkeletalMeshComponent* Mesh = nullptr;

    UPROPERTY(EditAnywhere)
	class USkeletalMeshComponent* WeaponMeshComp = nullptr;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Building)
    TSoftObjectPtr<class USkeletalMesh> WeaponMeshBase;

    UPROPERTY(VisibleAnywhere)
	class UBoxComponent* CollisionComponent = nullptr;

    UPROPERTY(EditDefaultsOnly)
    FName WeaponSocket = "WeaponSocket";

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	class UHonkMovementComponent* GetMovComp() { return MovComp; }

private:
    UPROPERTY(VisibleAnywhere)
    class USceneComponent* RootComp = nullptr;
	UPROPERTY(VisibleAnywhere)
    class USceneComponent* WeaponMountComp = nullptr;
	UPROPERTY(VisibleAnywhere)
	class UHonkMovementComponent* MovComp = nullptr;
	UPROPERTY(VisibleAnywhere)
    class UHonkWeaponComponent* WeaponComp = nullptr;
	/* Are we on a 'slippery' surface */
	bool bIsLowFriction;
};
