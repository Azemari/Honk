// Fill out your copyright notice in the Description page of Project Settings.

#include "Honk.h"
#include "HonkUIButton.h"

#define LOCTEXT_NAMESPACE "UMG"

UHonkUIButton::UHonkUIButton()
{
	static ConstructorHelpers::FObjectFinder<USlateWidgetStyleAsset> MyCustomStyle(TEXT("/Game/UserInterface/HonkUIButtonStyle"));

	SButton::FArguments ButtonDefaults;
	ButtonDefaults.ButtonStyle(MyCustomStyle.Object);
	WidgetStyle = *ButtonDefaults._ButtonStyle;
}

#if WITH_EDITOR
const FText UHonkUIButton::GetPaletteCategory()
{
	return LOCTEXT("", "Honk Buttons");
}
#endif

#undef LOCTEXT_NAMESPACE