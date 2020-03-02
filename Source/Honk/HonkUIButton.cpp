#include "HonkUIButton.h"


#define LOCTEXT_NAMESPACE "UMG"

UHonkUIButton::UHonkUIButton()
{
	static ConstructorHelpers::FObjectFinder<USlateWidgetStyleAsset> MyCustomStyle(TEXT("/Game/UserInterface/HonkUIButtonStyle.HonkUIButtonStyle"));
	SButton::FArguments ButtonDefaults;

	ButtonDefaults.ButtonStyle(MyCustomStyle.Object);
	WidgetStyle = *ButtonDefaults._ButtonStyle;
}

#if WITH_EDITOR
const FText UHonkUIButton::GetPaletteCategory()
{
	return LOCTEXT("", "Honk UI Button");
}

#endif
#undef LOCTEXT_NAMESPACE
