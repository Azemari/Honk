// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Runtime/UMG/Public/UMG.h"
#include "Components/Button.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "HonkUIButton.generated.h"

UCLASS()
class HONK_API UHonkUIButton : public UButton
{
	GENERATED_UCLASS_BODY()

		UHonkUIButton();

#if WITH_EDITOR
	virtual const FText GetPaletteCategory() override;
#endif
	
};
