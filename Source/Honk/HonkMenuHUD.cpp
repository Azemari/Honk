// Fill out your copyright notice in the Description page of Project Settings.


#include "HonkMenuHUD.h"
#include "Blueprint/UserWidget.h"

void AHonkMenuHUD::BeginPlay()
{
	Super::BeginPlay();

	if (MenuWidgetClass)
	{
		if (!MenuWidget)
		{
			MenuWidget = CreateWidget<UUserWidget>(GetWorld(), MenuWidgetClass);
			check(MenuWidget);
		}
	}

	if (OptionsWidgetClass)
	{
		if (!OptionsWidget)
		{
			OptionsWidget = CreateWidget<UUserWidget>(GetWorld(), OptionsWidgetClass);
			check(OptionsWidget);
		}
	}

	MenuWidget->AddToViewport();
	OptionsWidget->AddToViewport();
	ShowMainMenu();
}


void AHonkMenuHUD::ShowOptions() const
{
	MenuWidget->SetVisibility(ESlateVisibility::Hidden);
	OptionsWidget->SetVisibility(ESlateVisibility::Visible);
}

void AHonkMenuHUD::ShowMainMenu() const
{
	MenuWidget->SetVisibility(ESlateVisibility::Visible);
	OptionsWidget->SetVisibility(ESlateVisibility::Hidden);
}

void AHonkMenuHUD::HideUI() const
{
	MenuWidget->SetVisibility(ESlateVisibility::Hidden);
	OptionsWidget->SetVisibility(ESlateVisibility::Hidden);
}
