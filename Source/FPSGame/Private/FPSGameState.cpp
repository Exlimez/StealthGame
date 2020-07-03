// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSGameState.h"
#include <Runtime\Engine\Classes\Engine\World.h>
#include "FPSPlayerController.h"

void AFPSGameState::MulticastOnMissionCompleted_Implementation(APawn* InstigatorPawn, bool IsMissionCompleted)
{

	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; It++)
	{
		AFPSPlayerController* PC = Cast<AFPSPlayerController>(It->Get());

		if (PC && PC->IsLocalController())
		{
			PC->OnMissionComplete(InstigatorPawn, IsMissionCompleted);

			//Disable input
			APawn* Pawn = PC->GetPawn();
			if (Pawn)
			{
				Pawn->DisableInput(PC);
			}
		}
	}
}