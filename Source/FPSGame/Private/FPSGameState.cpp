// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSGameState.h"
#include <Runtime\Engine\Classes\Engine\World.h>

void AFPSGameState::MulticastOnMissionCompleted_Implementation(APawn* InstigatorPawn, bool IsMissionCompleted)
{
	for (FConstPawnIterator It = GetWorld()->GetPawnIterator(); It; It++)
	{
		APawn* Pawn = It->Get();
		if (Pawn && Pawn->IsLocallyControlled())
		{
			Pawn->DisableInput(nullptr);
		}
	}
}