// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OptionsWidget.generated.h"

/**
 * 
 */
UCLASS()
class HONK_API UOptionsWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnPlayerCountUpdated(FString SelectedItem, ESelectInfo::Type SelectionType);

	void DisplayAppropriateCarSelectors(int Players);
	UFUNCTION()
	void UpdateAllPlayerCars(FString UnusedString, ESelectInfo::Type UnusedSelectInfo) const;

protected:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UComboBoxString* PlayerCount;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UComboBoxString* PlayerOneCar;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UComboBoxString* PlayerTwoCar;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UComboBoxString* PlayerThreeCar;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UComboBoxString* PlayerFourCar;

};
