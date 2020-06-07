// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScoreWidget.generated.h"

/**
 * 
 */
UCLASS()
class HONK_API UScoreWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* FirstPlace;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* SecondPlace;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* ThirdPlace;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* ThirdPlaceHidableText;

};
