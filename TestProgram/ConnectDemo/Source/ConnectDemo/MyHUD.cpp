// Fill out your copyright notice in the Description page of Project Settings.

#include "MyHUD.h"

#include "StringConv.h"

void AMyHUD::BeginPlay()
{
    Super::BeginPlay();

    m_pWidget = CreateWidget<UMainUIWidget>(GetWorld(), WidgetClass);
    if (m_pWidget != nullptr)
        m_pWidget->AddToViewport();

    //I set anth process when HUD is created, you could also change your auth process into other time;

    APlayerController *myPlayerController = Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
    //设置鼠标输入模式
    if (myPlayerController != nullptr)
    {
        FInputModeGameOnly InputMode;
        InputMode.SetConsumeCaptureMouseDown(true);
        myPlayerController->SetInputMode(InputMode);
    }
}

void AMyHUD::Tick(float DeltaTime)
{
    m_pWidget->UpdateData();
}
