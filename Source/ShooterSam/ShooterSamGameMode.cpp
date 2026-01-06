// Copyright Epic Games, Inc. All Rights Reserved.

#include "ShooterSamGameMode.h"
#include "ShooterSamCharacter.h"
#include "ShooterAI.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/AmbientSound.h"


AShooterSamGameMode::AShooterSamGameMode()
{
	// stub
}

void AShooterSamGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (AShooterSamCharacter* Player = Cast<AShooterSamCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0))){
		MainShooterPlayer = Player;
		
		TArray<AActor*> Enemies;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AShooterAI::StaticClass(), Enemies);
		
		for (AActor* enemy : Enemies)
		{
			if (AShooterAI* enemyShooterAI = Cast<AShooterAI>(enemy)) {
				enemyShooterAI->StartBehaviorTree(Player);
			}	
		}
		NumberOfEnemiesLeft = Enemies.Num();
	}
	
}

void AShooterSamGameMode::ActorDied(AActor* DeadActor)
{
	if (DeadActor == MainShooterPlayer) {
		FTimerHandle GameOverTimerHandle;
		GetWorldTimerManager().SetTimer(GameOverTimerHandle, this, &AShooterSamGameMode::onGameOverTimerTimeOut, GameOverDelay, false);
	}
	else {
		if (Cast<AShooterSamCharacter>(DeadActor)) {
			NumberOfEnemiesLeft--;
			NumberOfKilledEnemies++;
			MainShooterPlayer->UpdateHUDEnemiesKilled(NumberOfKilledEnemies);
			if (NumberOfEnemiesLeft == 0) {
				MainShooterPlayer->ActivateVictory();
			}
		}
	}
}

int AShooterSamGameMode::GetNumOfEnemiesLeft()
{
	return NumberOfEnemiesLeft;
}

int AShooterSamGameMode::GetNumOfKilledEnemies()
{
	return NumberOfKilledEnemies;
}

void AShooterSamGameMode::onGameOverTimerTimeOut()
{
	//restarting current level to be improved in the future in efficiency.
	UGameplayStatics::OpenLevel(GetWorld(), FName(*UGameplayStatics::GetCurrentLevelName(GetWorld())));
}
