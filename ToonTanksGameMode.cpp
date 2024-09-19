// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "MyTankCharacter.h"
#include "MyEnemyTankCharacter.h"
#include "BrickWall.h"
#include "ToonTanksPlayerController.h"
void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
	if (DeadActor == MyTank)
	{
		MyTank->HandleDestruction();
		if (ToonTanksPlayerController)
		{
			ToonTanksPlayerController->SetPlayerEnabledState(false);
		}
		GameOver(false);
		
	}
	else if (AMyEnemyTankCharacter* DestoryedTower = Cast<AMyEnemyTankCharacter>(DeadActor))
	{
		DestoryedTower->HandleDestruction();
		--TargetTowers;
		if (TargetTowers == 0)
		{
			GameOver(true);
		}
	}
	else if (ABrickWall* DestoryedBrickWall = Cast<ABrickWall>(DeadActor))
	{
		DestoryedBrickWall->HandleDestruction();
	}
}

void AToonTanksGameMode::BeginPlay()
{
	Super::BeginPlay();
	HandleGameStart();
}

void AToonTanksGameMode::HandleGameStart()
{
	TargetTowers = GetTargetTowerCount();
	MyTank = Cast<AMyTankCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
	ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	StartGame();
	if (ToonTanksPlayerController)
	{
		ToonTanksPlayerController->SetPlayerEnabledState(false);
		FTimerHandle PlayerEnableTimerHandle;
		FTimerDelegate PlayerEnableTimerDelegate = 
			FTimerDelegate::CreateUObject(
				ToonTanksPlayerController,
				&AToonTanksPlayerController::SetPlayerEnabledState,
				true
			);
		GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle,
			PlayerEnableTimerDelegate,
			StartDelay,
			false);
	}
}

int32 AToonTanksGameMode::GetTargetTowerCount()
{
	TArray<AActor*> Towers;
	UGameplayStatics::GetAllActorsOfClass(this, AMyEnemyTankCharacter::StaticClass(),Towers);
	return Towers.Num();
}
