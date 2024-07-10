// Fill out your copyright notice in the Description page of Project Settings.

#include "CustomUserWidget.h"

UCustomUserWidget::UCustomUserWidget(const FObjectInitializer& objectInitializer) : Super(objectInitializer)
{


}

bool UCustomUserWidget::Initialize()
{
    if (!Super::Initialize())
    {
        return false;
    }

    if (UTextBlock* SText = Cast<UTextBlock>(GetWidgetFromName("TextBlock_1")))
    {
        TextBlock_1 = SText;
    }
    if (UTextBlock* SText = Cast<UTextBlock>(GetWidgetFromName("TextBlock_2")))
    {
        TextBlock_2 = SText;
    }
    if (UTextBlock* SText = Cast<UTextBlock>(GetWidgetFromName("TextBlock_3")))
    {
        TextBlock_3 = SText;
    }
    if (UTextBlock* SText = Cast<UTextBlock>(GetWidgetFromName("TextBlock_4")))
    {
        TextBlock_4 = SText;
    }
    if (UTextBlock* SText = Cast<UTextBlock>(GetWidgetFromName("TextBlock_5")))
    {
        TextBlock_5 = SText;
    }
    if (UTextBlock* SText = Cast<UTextBlock>(GetWidgetFromName("TextBlock_6")))
    {
        TextBlock_6 = SText;
    }
    if (UTextBlock* SText = Cast<UTextBlock>(GetWidgetFromName("TextBlock_7")))
    {
        TextBlock_7 = SText;
    }
    if (UTextBlock* SText = Cast<UTextBlock>(GetWidgetFromName("TextBlock_8")))
    {
        TextBlock_8 = SText;
    }

    return true;
}

void UCustomUserWidget::SetTextByIndex(FString  text, const int index)
{
    switch (index)
    {
        case 1:
            TextBlock_1->SetText(FText::FromString(text));
            break;
        case 2:
            TextBlock_2->SetText(FText::FromString(text));
            break;
        case 3:
            TextBlock_3->SetText(FText::FromString(text));
            break;
        case 4:
            TextBlock_4->SetText(FText::FromString(text));
            break;
        case 5:
            TextBlock_5->SetText(FText::FromString(text));
            break;
        case 6:
            TextBlock_6->SetText(FText::FromString(text));
            break;
        case 7:
            TextBlock_7->SetText(FText::FromString(text));
            break;
        case 8:
            TextBlock_8->SetText(FText::FromString(text));
            break;
        default:
            break;
    }
}
