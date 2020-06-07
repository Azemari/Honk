// Fill out your copyright notice in the Description page of Project Settings.


#include "OptionsWidget.h"
#include "HonkGameInstance.h"
#include "Components/ComboBoxString.h"

void UOptionsWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (UHonkGameInstance* GI = Cast<UHonkGameInstance>(GetGameInstance()))
	{
		if (GI->GetNumPlayers() > 0 && GI->GetNumPlayers() < 5)
		{
			PlayerCount->SetSelectedIndex(GI->GetNumPlayers() - 1);
		}
		else
		{
			PlayerCount->SetSelectedIndex(1);
			GI->SetNumPlayers(2);
		}
	}

	PlayerOneCar->SetSelectedIndex(0);
	PlayerTwoCar->SetSelectedIndex(0);
	PlayerThreeCar->SetSelectedIndex(0);
	PlayerFourCar->SetSelectedIndex(0);

	FScriptDelegate PlayerCountDelegate;
	PlayerCountDelegate.BindUFunction(this, FName("OnPlayerCountUpdated"));
	PlayerCount->OnSelectionChanged.Add(PlayerCountDelegate);

	FScriptDelegate PlayerCarDelegate;
	PlayerCarDelegate.BindUFunction(this, FName("UpdateAllPlayerCars"));
	PlayerOneCar->OnSelectionChanged.Add(PlayerCarDelegate);
	PlayerTwoCar->OnSelectionChanged.Add(PlayerCarDelegate);
	PlayerThreeCar->OnSelectionChanged.Add(PlayerCarDelegate);
	PlayerFourCar->OnSelectionChanged.Add(PlayerCarDelegate);
}

void UOptionsWidget::OnPlayerCountUpdated(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	if (UHonkGameInstance* GI = Cast<UHonkGameInstance>(GetGameInstance()))
	{
		GI->SetNumPlayers(PlayerCount->GetSelectedIndex() + 1);
		DisplayAppropriateCarSelectors(PlayerCount->GetSelectedIndex() + 1);
	}
}

void UOptionsWidget::DisplayAppropriateCarSelectors(int Players)
{
	//there must be at least one player
	PlayerOneCar->SetVisibility(ESlateVisibility::Visible);

	PlayerTwoCar->SetVisibility(ESlateVisibility::Hidden);
	PlayerThreeCar->SetVisibility(ESlateVisibility::Hidden);
	PlayerFourCar->SetVisibility(ESlateVisibility::Hidden);

	if (Players > 1)
	{
		PlayerTwoCar->SetVisibility(ESlateVisibility::Visible);
	}

	if (Players > 2)
	{
		PlayerThreeCar->SetVisibility(ESlateVisibility::Visible);
	}

	if (Players > 3)
	{
		PlayerFourCar->SetVisibility(ESlateVisibility::Visible);
	}
}

void UOptionsWidget::UpdateAllPlayerCars(FString UnusedString, ESelectInfo::Type UnusedSelectInfo) const
{
	if (UHonkGameInstance* GI = Cast<UHonkGameInstance>(GetGameInstance()))
	{
		GI->SetPlayerCar(0, PlayerOneCar->GetSelectedOption());
		GI->SetPlayerCar(1, PlayerTwoCar->GetSelectedOption());
		GI->SetPlayerCar(2, PlayerThreeCar->GetSelectedOption());
		GI->SetPlayerCar(3, PlayerFourCar->GetSelectedOption());
	}
}