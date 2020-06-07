// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerStart.h"
#include "HonkPlayerStart.generated.h"

/**
 * 
 */
UCLASS()
class HONK_API AHonkPlayerStart : public APlayerStart
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	int PlayerNum = 1;
};
