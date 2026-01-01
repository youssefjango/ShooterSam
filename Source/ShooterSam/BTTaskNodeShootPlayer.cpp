// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNodeShootPlayer.h"
#include <ShooterAI.h>

UBTTaskNodeShootPlayer::UBTTaskNodeShootPlayer()
{
	NodeName = TEXT("Shooting Player");
}

EBTNodeResult::Type UBTTaskNodeShootPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	if (AShooterAI* AIController = Cast<AShooterAI>(OwnerComp.GetAIOwner())) {
		if (AIController->MainShooterCharacter 
			&& AIController->ControlledCharacter 
			&& AIController->MainShooterCharacter->IsAlive) {
			AIController->ControlledCharacter->Shoot();
			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
	
}
