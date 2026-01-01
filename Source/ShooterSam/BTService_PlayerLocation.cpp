// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerLocation.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "ShooterAI.h"

UBTService_PlayerLocation::UBTService_PlayerLocation()
{
	NodeName = TEXT("Get Player Location");
}

void UBTService_PlayerLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	
	if (AShooterAI* AI = Cast<AShooterAI>(OwnerComp.GetAIOwner())) {
		AShooterSamCharacter* Player = AI->MainShooterCharacter;
		UBlackboardComponent* BB = OwnerComp.GetBlackboardComponent();
		if (Player && BB) {
			BB->SetValueAsVector(GetSelectedBlackboardKey(), Player->GetActorLocation());
		}
	}
}
