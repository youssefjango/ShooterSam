// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDWidget.h"

void UHUDWidget::setHealthBar(float percent)
{
	if (percent >= 0 && percent <= 1) {
		HealthBar->SetPercent(percent);
	}
}
