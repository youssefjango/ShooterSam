// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerLocationIfSeen.h"
#include "BehaviorTree/BlackboardComponent.h"

#include <ShooterAI.h>

UBTService_PlayerLocationIfSeen::UBTService_PlayerLocationIfSeen()
{
	NodeName = TEXT("Update PlayerLocation If Seen");
}

void UBTService_PlayerLocationIfSeen::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	if (AShooterAI* OwnerController = Cast<AShooterAI>(OwnerComp.GetAIOwner())) {
		AShooterSamCharacter* Player = OwnerController->MainShooterCharacter;
		UBlackboardComponent* BB = OwnerController->GetBlackboardComponent();
		if (Player && BB) {
			if (OwnerController->LineOfSightTo(Player)) {
				OwnerController->SetFocus(Player, EAIFocusPriority::Gameplay);
				BB->SetValueAsVector(GetSelectedBlackboardKey(), Player->GetActorLocation());
			}
			else {
				OwnerController->ClearFocus(EAIFocusPriority::Gameplay);
				BB->ClearValue(GetSelectedBlackboardKey());
			}
		}
	}

}
