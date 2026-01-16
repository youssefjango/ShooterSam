// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Gun.generated.h"

UCLASS()
class SHOOTERSAM_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	USceneComponent* GunRoot;

	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* mesh;
	UPROPERTY(EditAnywhere)
	float AimFactor = 10.0f;
	UPROPERTY(EditAnywhere)
	float MaxRange = 200.0f;
	UPROPERTY(EditAnywhere)
	float BulletDamage = 20.0f;

	UPROPERTY(EditAnywhere)
	float fireRate = -1.0f; //negative number to 0 means that it is not automatic
	AController* OwnerConroller;

	UPROPERTY(EditAnywhere, Category = "Particles Systems")
	UNiagaraComponent* MuzzleFlashParticleSystem;

	UPROPERTY(EditAnywhere, Category = "Particles Systems")
	UNiagaraSystem* ImpactParticleSystem;

	UPROPERTY(EditAnywhere, Category = "Sound Cues")
	USoundBase* ShootSound;
	UPROPERTY(EditAnywhere, Category = "Sound Cues")
	USoundBase* ImpactSound;

	void PullTrigger(bool IsAiming);

	void StopShooting();
private:
	FTimerHandle AutoFireTimer;
	void ShootBullet(bool IsAiming);
};
