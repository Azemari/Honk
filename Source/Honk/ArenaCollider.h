// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "ArenaCollider.generated.h"

UCLASS()
class HONK_API AArenaCollider : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AArenaCollider();
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	UBoxComponent* ArenaCollider1 = nullptr;
	UPROPERTY(EditAnywhere)
	UBoxComponent* ArenaCollider2 = nullptr;
	UPROPERTY(EditAnywhere)
	UBoxComponent* ArenaCollider3 = nullptr;
	UPROPERTY(EditAnywhere)
	UBoxComponent* ArenaCollider4 = nullptr;
	UPROPERTY(EditAnywhere)
	UBoxComponent* ArenaCollider5 = nullptr;
	UPROPERTY(EditAnywhere)
	UBoxComponent* ArenaCollider6 = nullptr;
	UPROPERTY(EditAnywhere)
	UBoxComponent* ArenaCollider7 = nullptr;
	UPROPERTY(EditAnywhere)
	UBoxComponent* ArenaCollider8 = nullptr;
	UPROPERTY(EditAnywhere)
	UBoxComponent* ArenaCollider9 = nullptr;
	UPROPERTY(EditAnywhere)
	UBoxComponent* ArenaCollider10 = nullptr;
	UPROPERTY(EditAnywhere)
	UBoxComponent* ArenaCollider11 = nullptr;
	UPROPERTY(EditAnywhere)
	UBoxComponent* ArenaCollider12 = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
