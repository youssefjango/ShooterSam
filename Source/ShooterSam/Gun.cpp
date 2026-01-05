// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Kismet/GameplayStatics.h"

#define LOG_WARNING(x) UE_LOG(LogTemp, Warning, TEXT(x))

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GunRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Gun Root"));

	SetRootComponent(GunRoot);

	mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	mesh->SetupAttachment(GunRoot);

	MuzzleFlashParticleSystem = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Muzzle Flash Particle"));
	MuzzleFlashParticleSystem->SetupAttachment(mesh);
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();

	MuzzleFlashParticleSystem->Deactivate();
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGun::PullTrigger()
{
	if (OwnerConroller) {
		ShootBullet();
		if (fireRate > 0.0f) {
			GetWorldTimerManager().SetTimer(AutoFireTimer, this,&AGun::ShootBullet, 1.0f/fireRate, true);
		}
	}
}

void AGun::ShootBullet() {
	//Activating Shooting particles and Playing Sound
	MuzzleFlashParticleSystem->Activate(true);
	if (ShootSound) {
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), ShootSound, MuzzleFlashParticleSystem->GetComponentLocation());
	}
	else {
		UE_LOG(LogTemp, Display, TEXT("Shooting sound cue is not instantiated in the editor."));
	}
	FVector location;
	FRotator rotation;
	OwnerConroller->GetPlayerViewPoint(location, rotation);
	FVector endLocation = location + MaxRange * rotation.Vector();
	FHitResult hitRes;
	FCollisionQueryParams params;
	params.AddIgnoredActor(this);
	params.AddIgnoredActor(GetOwner());
	bool hasHit = GetWorld()->LineTraceSingleByChannel(hitRes, location, endLocation, ECC_GameTraceChannel2, params);
	if (hasHit) {
		if (ImpactParticleSystem) {
			//Playing Sound and particles
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), ImpactParticleSystem, hitRes.ImpactPoint, hitRes.ImpactPoint.Rotation());
			if (ImpactSound) {
				UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactSound, hitRes.ImpactPoint);
			}
			else {
				UE_LOG(LogTemp, Display, TEXT("Impact sound cue is not instantiated in the editor."));
			}
		}
		else {
			UE_LOG(LogTemp, Display, TEXT("Impact particle system is not instantiated in the editor."));
		}
		if (AActor* hitActor = Cast<AActor>(hitRes.GetActor())) {
			UGameplayStatics::ApplyDamage(hitActor, BulletDamage
				, OwnerConroller, this, UDamageType::StaticClass());
		}
	}
}

void AGun::StopShooting()
{
	GetWorldTimerManager().ClearTimer(AutoFireTimer);
}

