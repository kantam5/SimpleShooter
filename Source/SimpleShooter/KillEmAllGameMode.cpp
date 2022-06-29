// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode.h"
#include "ShooterPlayerController.h"

void AKillEmAllGameMode::PawnKilled(APawn* PawnKilled)
{
	Super::PawnKilled(PawnKilled);

	APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());
	if (PlayerController)
	{
		// view를 지정한 Actor로 넘긴다. 
		PlayerController->GameHasEnded();
	}
}
