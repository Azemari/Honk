// Fill out your copyright notice in the Description page of Project Settings.


#include "OptionsWidget.h"
#include "HonkGameInstance.h"
#include "Components/ComboBoxString.h"

void UOptionsWidget::NativeConstruct()
{
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

	FScriptDelegate Delegate;
	Delegate.BindUFunction(this, FName("OnPlayerCountUpdated"));
	PlayerCount->OnSelectionChanged.Add(Delegate);
}

void UOptionsWidget::OnPlayerCountUpdated(FString SelectedItem, ESelectInfo::Type SelectionType) const
{
	if (UHonkGameInstance* GI = Cast<UHonkGameInstance>(GetGameInstance()))
	{
		GI->SetNumPlayers(PlayerCount->GetSelectedIndex() + 1);
	}
}