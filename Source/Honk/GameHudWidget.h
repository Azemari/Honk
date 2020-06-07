// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameHudWidget.generated.h"

/**
 * 
 */
UCLASS()
class HONK_API UGameHudWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent)
	void AddPlayer(int currentLives, int currentHealth, FName currentWeapon, int32 idx);
	void AddPlayer_Implementation(int currentLives, int currentHealth, FName currentWeapon, int32 idx){}
	UFUNCTION(BlueprintNativeEvent)
	void UpdatePlayer(int currentLives, int currentHealth, FName currentWeapon, int32 idx);
	void UpdatePlayer_Implementation(int currentLives, int currentHealth, FName currentWeapon, int32 idx){}
};