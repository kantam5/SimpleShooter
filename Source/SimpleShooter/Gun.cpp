// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
}

void AGun::PullTrigger()
{
	if (MuzzleFlash)
	{
		UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));
	}

	FVector CameraLocation;
	FRotator CameraRotation;
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn)
	{
		AController* OwnerController = OwnerPawn->GetController();
		if (OwnerController)
		{
			OwnerController->GetPlayerViewPoint(CameraLocation, CameraRotation);
		}
	}
	FVector End = CameraLocation + CameraRotation.Vector() * MaxRange;

	FHitResult HitResult;
	bool bHit = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		CameraLocation,
		End,
		ECollisionChannel::ECC_GameTraceChannel1
	);

	DrawDebugSphere(GetWorld(), End, 20.0f, 12, FColor::Blue, false, 1.0f);

	if (bHit)
	{
		if (HitResult.GetActor() == OwnerPawn)
		{
			return;
		}
		else
		{
			FVector ShotDirection = -CameraRotation.Vector();
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, HitResult.Location, ShotDirection.Rotation());
		}
	}
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

