// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "ShooterSamGameMode.generated.h"

/**
 *  Simple GameMode for a third person game
 */
UCLASS(abstract)
class AShooterSamGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	
	/** Constructor */
	AShooterSamGameMode();
protected:
	virtual void BeginPlay() override;
private:
	//making sure they will never get modified accidentally
	int NumberOfEnemiesLeft;
	int NumberOfKilledEnemies = 0;
	TArray<AActor*> Enemies;
public:
	UPROPERTY(EditAnywhere, Category = "Game Over Respawn")
	float GameOverDelay = 5.0f;

	class AShooterSamCharacter* MainShooterPlayer;
	void onGameOverTimerTimeOut();
	void ActorDied(AActor* DeadActor);
	int GetNumOfEnemiesLeft();
	int GetNumOfKilledEnemies();
	void HighlightEnemies(UMaterialInterface* HighlightMaterial);

	void UnhighlightEnemies();

};



