// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HonkExplosion.generated.h"

UCLASS()
class HONK_API AHonkExplosion : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHonkExplosion();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	UFUNCTION(BlueprintNativeEvent)
	void OnExplode();
	void OnExplode_Implementation() {}	
	UPROPERTY(BlueprintReadOnly)
	float Radius = 0;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void Initialise(float radius, float damage);

private:
	float Damage = 0;

};
