// Copyright Epic Games, Inc. All Rights Reserved.

#include "ShooterSamGameMode.h"
#include "ShooterSamCharacter.h"
#include "ShooterAI.h"
#include "Kismet/GameplayStatics.h"


AShooterSamGameMode::AShooterSamGameMode()
{
	// stub
}

void AShooterSamGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (AShooterSamCharacter* Player = Cast<AShooterSamCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0))){
		TArray<AActor*> Enemies;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AShooterAI::StaticClass(), Enemies);
		
		for (AActor* enemy : Enemies)
		{
			if (AShooterAI* enemyShooterAI = Cast<AShooterAI>(enemy)) {
				enemyShooterAI->StartBehaviorTree(Player);
			}	
		}
	}
}
