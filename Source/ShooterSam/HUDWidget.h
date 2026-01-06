// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "HUDWidget.generated.h"


/**
 * 
 */
UCLASS()
class SHOOTERSAM_API UHUDWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UProgressBar* HealthBar;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* TB_EnemiesKilled;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* TB_TimeLeft;
	void setHealthBar(float percent);
	void setEnemiesKilled(int enemies);
};
