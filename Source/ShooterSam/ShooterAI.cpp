// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAI.h"
#include "ShooterSamCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

AShooterAI::AShooterAI() {
	AIPerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));

	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));

	SightConfig->SightRadius = 2500.f;
	SightConfig->LoseSightRadius = 3000.f;
	SightConfig->PeripheralVisionAngleDegrees = 90.f;
	SightConfig->SetMaxAge(3.0f);
	SightConfig->AutoSuccessRangeFromLastSeenLocation = 520.f;

	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	AIPerceptionComp->ConfigureSense(*SightConfig);
	AIPerceptionComp->SetDominantSense(UAISense_Sight::StaticClass());
}
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