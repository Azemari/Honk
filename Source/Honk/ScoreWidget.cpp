// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreWidget.h"
#include "Components/TextBlock.h"
#include "HonkGameInstance.h"

void UScoreWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (UHonkGameInstance* GI = Cast<UHonkGameInstance>(GetGameInstance()))
	{
		TArray<int> LoserOrder = GI->GetLosingPlayers();
		const FString PlayerText = "Player ";
		if (LoserOrder.Num() == 2)
		{
			FString FirstPlaceText = PlayerText;
			FirstPlaceText.AppendInt(LoserOrder[1] + 1);
			FirstPlace->SetText(FText::FromString(FirstPlaceText));

			FString SecondPlaceText = PlayerText;
			SecondPlaceText.AppendInt(LoserOrder[0] + 1);
			SecondPlace->SetText(FText::FromString(SecondPlaceText));

			ThirdPlaceHidableText->SetText(FText::FromString(""));
		}
		else if(LoserOrder.Num() == 4)
		{
			LoserOrder.RemoveAt(0);
		}
		if (LoserOrder.Num() == 3)
		{
			FString FirstPlaceText = PlayerText;
			FirstPlaceText.AppendInt(LoserOrder[2] + 1);
			FirstPlace->SetText(FText::FromString(FirstPlaceText));

			FString SecondPlaceText = PlayerText;
			SecondPlaceText.AppendInt(LoserOrder[1] + 1);
			SecondPlace->SetText(FText::FromString(SecondPlaceText));

			FString ThirdPlaceText = PlayerText;
			ThirdPlaceText.AppendInt(LoserOrder[0] + 1);
			ThirdPlace->SetText(FText::FromString(ThirdPlaceText));
		}
		GI->ClearLosingPlayers();
	}

}