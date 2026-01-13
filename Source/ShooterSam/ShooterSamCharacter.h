// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "Gun.h"
#include "ShooterSamGameMode.h"
#include "Components/PostProcessComponent.h"


#include "ShooterSamCharacter.generated.h"



class USpringArmComponent;
class UCameraComponent;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

/**
 *  A simple player-controllable third person character
 *  Implements a controllable orbiting camera
 */
UCLASS(abstract)
class AShooterSamCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
protected:

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* LookAction;

	/** Mouse Look Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* MouseLookAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* ShootAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* AimAction;
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* SlowMotionAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* RunAction;

public:

	/** Constructor */
	AShooterSamCharacter();	

protected:

	/** Initialize input action bindings */
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void BeginPlay() override;
protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

public:

	/** Handles move inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoMove(float Right, float Forward);

	/** Handles look inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoLook(float Yaw, float Pitch);

	/** Handles jump pressed inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoJumpStart();

	/** Handles jump pressed inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoJumpEnd();

public:

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	UPROPERTY(EditAnywhere)
	TSubclassOf<AGun> GunClass;
	UPROPERTY(VisibleAnywhere)
	AGun* gunActor;
	UPROPERTY(EditAnywhere)
	float MaxHealth = 100.0f;

	float Health;

	UPROPERTY(BlueprintReadOnly)
	bool IsAlive = true;
	UPROPERTY(EditAnywhere, Category = "Ability")
	float SlowMotionRate = 1.0f;
	UPROPERTY(EditAnywhere, Category = "Sound Cues")
	USoundBase* JumpSound;
	UPROPERTY(EditAnywhere, Category = "Sound Cues")
	USoundBase* FirstShootSound;
	UPROPERTY(EditAnywhere, Category = "Sound Cues")
	USoundBase* DeathSound;
	UPROPERTY(EditAnywhere, Category = "Sound Cues")
	USoundBase* PainSound;
	UPROPERTY(EditAnywhere, Category = "Sound Cues")
	USoundBase* LowHPSound;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool IsMissionComplete = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool IsRunning = false;

	AShooterSamGameMode* SSGM;
	UPROPERTY(EditAnywhere)
	float SprintingSpeed;
	UPROPERTY(EditAnywhere)
	float WalkingSpeed = 500.0f;
	//Postproccess volume for slowmotion
	UPROPERTY(EditAnywhere)
	UPostProcessComponent* PPV_SlowmoVision;

	//Highlight material
	UPROPERTY(EditAnywhere)
	UMaterialInterface* M_Hightlight;
	TArray<UMaterialInterface*> meshMaterials;
	void Shoot();
	void StopShoot();
	void Aim();
	void StopAim();
	void StartSlowMotion();
	void EndSlowMotion();
	void StartSprint();
	void StopSprint();
	UFUNCTION()
	void OnDamageTaken(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
	
	void ActivateVictory();

	void UpdateHUDHealthBar();

	void UpdateHUDEnemiesKilled(int enemiesLeft);
	
private:
	bool bIsInslowMotion = false;
	float DefaultArmLength;
	float LastPlayedTime = 0.0f;
	USoundBase* LastPlayedSound;
};

