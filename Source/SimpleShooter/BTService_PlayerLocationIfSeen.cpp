// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerLocationIfSeen.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_PlayerLocationIfSeen::UBTService_PlayerLocationIfSeen()
{
	NodeName = "Update Player Location If Seen";
}

void UBTService_PlayerLocationIfSeen::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (PlayerPawn == nullptr)
	{
		return;
	}

	AAIController* Controller = OwnerComp.GetAIOwner();
	if (Controller == nullptr)
	{
		return;
	}

	if (Controller->LineOfSightTo(PlayerPawn))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), PlayerPawn->GetActorLocation());
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
	}
}
