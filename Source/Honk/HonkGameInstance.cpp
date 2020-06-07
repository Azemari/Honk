// Fill out your copyright notice in the Description page of Project Settings.


#include "HonkGameInstance.h"

void UHonkGameInstance::Init()
{
	Super::Init();
	PlayerCars.Init("Camero", 4);
}

void UHonkGameInstance::SetPlayerCar(int PlayerNum, FString CarName)
{
	if (PlayerNum >= 0 && PlayerNum < 4)
	{
		PlayerCars[PlayerNum] = CarName;
	}
}

FString UHonkGameInstance::GetPlayerCar(int PlayerNum)
{
	if (PlayerNum >= 0 && PlayerNum < 4)
	{
		return PlayerCars[PlayerNum];
	}
	return "Camero";
}