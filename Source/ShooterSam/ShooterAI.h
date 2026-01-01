// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ShooterSamCharacter.h"
#include "ShooterAI.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERSAM_API AShooterAI : public AAIController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere)
	UBehaviorTree* EnemyAIBT;

	AShooterSamCharacter* MainShooterCharacter;
	
	AShooterSamCharacter* ControlledCharacter;

	void StartBehaviorTree(AShooterSamCharacter* Character);

};
