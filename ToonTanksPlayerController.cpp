// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksPlayerController.h"
#include "GameFramework/Pawn.h"
void AToonTanksPlayerController::SetPlayerEnabledState(bool bPLayerEnabled)
{
	UE_LOG(LogTemp, Display, TEXT("PC Enable"));
	if (bPLayerEnabled)
	{
		GetPawn()->EnableInput(this);

	}
	else
	{
		GetPawn()->DisableInput(this);
	}
	bShowMouseCursor = bPLayerEnabled;
}
