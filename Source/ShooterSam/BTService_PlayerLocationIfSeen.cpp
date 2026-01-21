// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerLocationIfSeen.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AISense_Sight.h"


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
			// Get the perception component from the ai controller
			auto* perceptionComponent = Cast<UAIPerceptionComponent>(OwnerController->GetAIPerceptionComponent());
			if (!IsValid(perceptionComponent))
			{
				return;
			}

			// Check all the perception stimuli of the actor (sight, hearing, etc)
			FActorPerceptionBlueprintInfo Info;
			perceptionComponent->GetActorsPerception(Player, Info);

			// loop through the list of stimuli until it gets to the sight type and check if its succesfully "sensed" (ie successfully in sight)
			bool isSeen = false;
			for (const FAIStimulus& stimulus : Info.LastSensedStimuli)
			{
				if (stimulus.Type == UAISense::GetSenseID(UAISense_Sight::StaticClass()))
				{
					isSeen = stimulus.WasSuccessfullySensed();
					break;
				}
			}
			if (isSeen) {
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
