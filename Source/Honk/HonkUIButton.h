#pragma once

#include "Runtime/UMG/Public/UMG.h"
#include "Components/Button.h"

#include "HonkUIButton.generated.h"

UCLASS()
class HONK_API UHonkUIButton : public UButton
{
	GENERATED_BODY()

	//UHonkUIButton();

#if WITH_EDITOR
	virtual const FText GetPaletteCategory() override;
#endif

};
