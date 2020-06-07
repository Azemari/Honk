// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HonkMenuHUD.generated.h"

/**
 * 
 */
UCLASS()
class HONK_API AHonkMenuHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void ShowOptions() const;

	UFUNCTION(BlueprintCallable)
	void ShowMainMenu() const;

	UFUNCTION(BlueprintCallable)
	void HideUI() const;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class UUserWidget> MenuWidgetClass;

	// The instance of the players Inventory UI Widget
	UPROPERTY(Transient, BlueprintReadOnly)
	class UUserWidget* MenuWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class UUserWidget> OptionsWidgetClass;

	// The instance of the players Inventory UI Widget
	UPROPERTY(Transient, BlueprintReadOnly)
	class UUserWidget* OptionsWidget;

};
