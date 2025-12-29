// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GunRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Gun Root"));

	SetRootComponent(GunRoot);

	mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	mesh->SetupAttachment(GunRoot);
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();

	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGun::PullTrigger()
{
	if (OwnerConroller) {
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
			DrawDebugSphere(GetWorld(), hitRes.ImpactPoint, 10.0f, 16, FColor::Red, true);
		}
	}
}

