// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "HonkPawn.generated.h"


UCLASS(config=Game)
class AHonkPawn : public APawn
{
	GENERATED_BODY()

public:
	AHonkPawn(const FObjectInitializer& ObjectInitializer);

	// Begin Pawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End Pawn interface

	// Begin Actor interface
	virtual void Tick(float Delta) override;
protected:
	virtual void BeginPlay() override;

public:
	// End Actor interface

	/** Handle pressing forwards */
	void MoveForward(float Val);

	/** Handle pressing right */
	void MoveRight(float Val);
	/** Handle handbrake pressed */
	void OnHandbrakePressed();
	/** Handle handbrake released */
	void OnHandbrakeReleased();


    UPROPERTY(VisibleAnywhere)
	class USkeletalMeshComponent* Mesh = nullptr;

    UPROPERTY(Transient)
	class USkeletalMeshComponent* WeaponMeshComp = nullptr;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Building)
    TSoftObjectPtr<class USkeletalMesh> WeaponMeshBase;


	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* CollisionComponent = nullptr;

    UPROPERTY(EditDefaultsOnly)
    FName WeaponSocket = "WeaponSocket";

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	UPROPERTY(VisibleAnywhere)
	class UHonkMovementComponent* MovComp = nullptr;
	/* Are we on a 'slippery' surface */
	bool bIsLowFriction;
};
