// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawner.h"
#include "Kismet/KismetMathLibrary.h"
#include <ShooterSamGameMode.h>
#include <Kismet/GameplayStatics.h>
// Sets default values
ASpawner::ASpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpawner::BeginPlay()
{
	Super::BeginPlay();
	if (AGameModeBase* GM = UGameplayStatics::GetGameMode(GetWorld())) {
		SSGM = Cast<AShooterSamGameMode>(GM);
	}
	if (SSGM) {
		GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &ASpawner::OnSpawn, SpawningRate, true);
	}
}

// Called every frame
void ASpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void ASpawner::OnSpawn() {

	if (UKismetMathLibrary::RandomBoolWithWeight(SpawningProbability)) {
		AShooterSamCharacter* Enemy = GetWorld()->SpawnActor<AShooterSamCharacter>(SpawnerShooterClass,GetTransform());
		SSGM->AddEnemy(Enemy);
	}
}

