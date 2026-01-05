// Copyright Epic Games, Inc. All Rights Reserved.

#include "ShooterSamCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Math/UnrealMathUtility.h"
#include "ShooterSamPlayerController.h"
#include "ShooterSam.h"
#include "Kismet/GameplayStatics.h"

#define PLAYSOUND(soundcue) if ((!LastPlayedSound || (GetWorld()->GetTimeSeconds() - LastPlayedTime > LastPlayedSound->Duration)) && soundcue) { LastPlayedTime = GetWorld()->GetTimeSeconds(); UGameplayStatics::PlaySoundAtLocation(GetWorld(), soundcue, GetActorLocation()); LastPlayedSound = soundcue;}
AShooterSamCharacter::AShooterSamCharacter()
{
	GetMesh()->HideBoneByName("weapon_r", EPhysBodyOp::PBO_None);
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	if (AGameModeBase* GM = UGameplayStatics::GetGameMode(GetWorld())) {
		SSGM = Cast<AShooterSamGameMode>(GM);
	}
	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

void AShooterSamCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	OnTakeAnyDamage.AddDynamic(this, &AShooterSamCharacter::OnDamageTaken);
	Health = MaxHealth;
	UpdateHUDHealthBar();

	gunActor = GetWorld()->SpawnActor<AGun>(GunClass);
	if (gunActor) {
		gunActor->SetOwner(this);
		gunActor->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
		gunActor->OwnerConroller = GetController();
	}
	

}

void AShooterSamCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AShooterSamCharacter::Move);
		EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &AShooterSamCharacter::Look);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AShooterSamCharacter::Look);

		// Shooting
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Started, this, &AShooterSamCharacter::Shoot);

		//Aiming Start
		EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Started, this, &AShooterSamCharacter::Aim);

		//Aiming Release
		EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Completed, this, &AShooterSamCharacter::StopAim);
	}
	else {
		UE_LOG(LogShooterSam, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}


void AShooterSamCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	// route the input
	DoMove(MovementVector.X, MovementVector.Y);
}

void AShooterSamCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	// route the input
	DoLook(LookAxisVector.X, LookAxisVector.Y);
}

void AShooterSamCharacter::DoMove(float Right, float Forward)
{
	if (GetController() != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = GetController()->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, Forward);
		AddMovementInput(RightDirection, Right);
	}
}

void AShooterSamCharacter::DoLook(float Yaw, float Pitch)
{
	if (GetController() != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(Yaw);
		AddControllerPitchInput(Pitch);
	}
}

void AShooterSamCharacter::DoJumpStart()
{
	// signal the character to jump
	Jump();
	PLAYSOUND(JumpSound);
}

void AShooterSamCharacter::DoJumpEnd()
{
	// signal the character to stop jumping
	StopJumping();
}

void AShooterSamCharacter::Shoot()
{
	if (gunActor) {
		gunActor->PullTrigger();
	}
	
	PLAYSOUND(FirstShootSound);
}
void AShooterSamCharacter::AutomaticShoot()
{
	if (gunActor) {
		gunActor->PullTrigger();
	}
}

void AShooterSamCharacter::Aim()
{
	auto CamBoom = GetCameraBoom();
	if (gunActor && CamBoom) {
		CamBoom->TargetArmLength = CamBoom->TargetArmLength / gunActor->AimFactor;
	}
}

void AShooterSamCharacter::StopAim()
{
	auto CamBoom = GetCameraBoom();
	if (gunActor && CamBoom) {
		CamBoom->TargetArmLength = CamBoom->TargetArmLength * gunActor->AimFactor;
	}
}

void AShooterSamCharacter::OnDamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (IsAlive) {
		Health -= Damage;
		UpdateHUDHealthBar();
		if (Health <= 0.0f) {
			Health = 0.0f;
			IsAlive = false;
			GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			DetachFromControllerPendingDestroy();
			PLAYSOUND(DeathSound);
			Cast<AShooterSamGameMode>(UGameplayStatics::GetGameMode(GetWorld()))->ActorDied(this);
		}
		else if (Health / MaxHealth <= 0.5f) {
			PLAYSOUND(LowHPSound);
		}
		else if (FMath::RandBool()) {
			PLAYSOUND(PainSound);
		}
	}
	

}

void AShooterSamCharacter::ActivateVictory()
{
	if (AShooterSamPlayerController* PC = Cast<AShooterSamPlayerController>(this->GetController())) {
		DisableInput(PC);
		IsMissionComplete = true;
	}
}

void AShooterSamCharacter::UpdateHUDHealthBar()
{
	if (AShooterSamPlayerController* PlayerController = Cast<AShooterSamPlayerController>(GetController())) {
		PlayerController->HUDWidget->setHealthBar(FMath::Clamp((Health / MaxHealth), 0.0f, 1.0f));
	}
}
