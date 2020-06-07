// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "HonkGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class HONK_API UHonkGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	virtual void Init() override;

	UFUNCTION(BlueprintCallable)
	void SetNumPlayers(int PlayerNum) { PlayerCount = PlayerNum; }
	UFUNCTION(BlueprintCallable)
	int GetNumPlayers() { return PlayerCount; }

	UFUNCTION()
	void SetPlayerCar(int PlayerNum, FString CarName);
	UFUNCTION()
	FString GetPlayerCar(int PlayerNum);

private:
	int PlayerCount = 2;
	TArray<FString> PlayerCars;
};
