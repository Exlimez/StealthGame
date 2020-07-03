// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FPSGameMode.h"
#include "FPSHUD.h"
#include "FPSCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "FPSGameState.h"
#include <Runtime\Engine\Classes\Engine\World.h>

AFPSGameMode::AFPSGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/BP_Player"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFPSHUD::StaticClass();

	GameStateClass = AFPSGameState::StaticClass();
}

void AFPSGameMode::CompleteMission(APawn* InstigatorPawn, bool IsMissionCompleted)
{
	if(InstigatorPawn)
	{
		//InstigatorPawn->DisableInput(nullptr);

		if(SpectatingViewpointClass)
		{
			AActor* NewViewTarget = nullptr;

			TArray<AActor*> ReturnedActors;

			UGameplayStatics::GetAllActorsOfClass(this, SpectatingViewpointClass, ReturnedActors);

			if (ReturnedActors.Num() > 0)
			{
				NewViewTarget = ReturnedActors[0];

				for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; It++)
				{
					APlayerController* PC = It->Get();

					if (PC)
					{
						PC->SetViewTargetWithBlend(NewViewTarget, 0.5, EViewTargetBlendFunction::VTBlend_Cubic);
					}
				}
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Spectating viewpoint class in nullptr. Please update GameMode class with valid subclass"))
		}
	}

	AFPSGameState* GS = GetGameState<AFPSGameState>();
	if (GS)
	{
		GS->MulticastOnMissionCompleted(InstigatorPawn, IsMissionCompleted);
	}

	OnMissionCompleted(InstigatorPawn, IsMissionCompleted);

}
