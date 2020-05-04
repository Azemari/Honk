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
