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

void AShooterSamGameMode::HighlightEnemies(UMaterialInterface* HighlightMaterial)
{
	if (Enemies.Num() > 0) {
		for (AActor* enemy : Enemies) {
			if (AShooterAI* enemyShooterAI = Cast<AShooterAI>(enemy)) {
				if (AShooterSamCharacter* shooter = Cast<AShooterSamCharacter>(enemyShooterAI->GetPawn())) {
					for (int32 i = 0; i < shooter->GetMesh()->GetNumMaterials(); i++)
					{
						shooter->meshMaterials[i] = shooter->GetMesh()->GetMaterial(i);
						shooter->GetMesh()->SetMaterial(i, HighlightMaterial);
					}
				}
			}
		}
	}
}
void AShooterSamGameMode::UnhighlightEnemies()
{
	if (Enemies.Num() > 0) {
		for (AActor* enemy : Enemies) {
			if (AShooterAI* enemyShooterAI = Cast<AShooterAI>(enemy)) {
				if (AShooterSamCharacter* shooter = Cast<AShooterSamCharacter>(enemyShooterAI->GetPawn())) {
					for (int32 i = 0; i < shooter->GetMesh()->GetNumMaterials(); i++)
					{
						shooter->GetMesh()->SetMaterial(i, shooter->meshMaterials[i]);
					}
				}
			}
		}
	}
}

void AShooterSamGameMode::AddEnemy(AShooterSamCharacter* Enemy)
{
	Enemies.Add(Enemy);
}

void AShooterSamGameMode::onGameOverTimerTimeOut()
{
	//restarting current level to be improved in the future in efficiency.
	UGameplayStatics::OpenLevel(GetWorld(), FName(*UGameplayStatics::GetCurrentLevelName(GetWorld())));
}
