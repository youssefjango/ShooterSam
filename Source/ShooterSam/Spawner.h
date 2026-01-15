// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ShooterSamCharacter.h"
#include "Spawner.generated.h"

UCLASS()
class SHOOTERSAM_API ASpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawner();
	UPROPERTY(EditAnywhere)
	TSubclassOf<AShooterSamCharacter> SpawnerShooterClass;

	UPROPERTY(EditAnywhere, 
		meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
	float SpawningProbability = 1.0f; //determines wether or not it chooses to spawn should be between 0 and 1

	UPROPERTY(EditAnywhere)
	float SpawningRate = 10.0f; // every SpawningRate seconds

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void OnSpawn();
private:
	FTimerHandle SpawnTimerHandle;
	class AShooterSamGameMode* SSGM;
};
