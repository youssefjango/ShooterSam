// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAI.h"
#include "ShooterSamCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

void AShooterAI::BeginPlay()
{
	Super::BeginPlay();
}

void AShooterAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/*if (AShooterSamCharacter* CurrentCharacter = Cast<AShooterSamCharacter>(GetCharacter())) {
		if (LineOfSightTo(PlayerPawn)) {
			SetFocus(PlayerPawn);
			MoveToActor(PlayerPawn, 200.0f);
		}
		else
		{
			ClearFocus(EAIFocusPriority::Gameplay);
			StopMovement();
		}
	*/	
		
		
		/*if (CurrentCharacter->gunActor) {
			MoveToActor(PlayerPawn, CurrentCharacter->gunActor->MaxRange);
			UE_LOG(LogTemp, Display, TEXT("has max rang because of gun"));
		}
		else {
			MoveToActor(PlayerPawn, 200.0f);
			UE_LOG(LogTemp, Display, TEXT("Gun not found"));
		}*/
}

void AShooterAI::StartBehaviorTree(AShooterSamCharacter* PlayerCharacter)
{
	if (EnemyAIBT) {
		ControlledCharacter = Cast<AShooterSamCharacter>(GetPawn());

		if (PlayerCharacter) {
			MainShooterCharacter = PlayerCharacter;
		}
		RunBehaviorTree(EnemyAIBT);

		if (UBlackboardComponent* BB = GetBlackboardComponent()) {
			if (MainShooterCharacter && ControlledCharacter) {
				BB->SetValueAsVector("OriginalLocation", ControlledCharacter->GetActorLocation());
			}
		}
	}
}