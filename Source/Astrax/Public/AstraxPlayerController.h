// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h"
#include "AstraxPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class ASTRAX_API AAstraxPlayerController : public APlayerController
{
	GENERATED_BODY()

public :

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = HUDOverlay)
		TSubclassOf<UUserWidget> UserWidgetAsset;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = HUDOverlay)
		UUserWidget* HUDOverlay;

protected:

	virtual void BeginPlay() override;
	
};
