// Fill out your copyright notice in the Description page of Project Settings.


#include "AstraxPlayerController.h"

void AAstraxPlayerController::BeginPlay()
{
	if (UserWidgetAsset)
	{
		HUDOverlay = CreateWidget<UUserWidget>(this, UserWidgetAsset);
	}

	if (HUDOverlay)
	{
		HUDOverlay->AddToViewport();
		HUDOverlay->SetVisibility(ESlateVisibility::Visible);
	}
}