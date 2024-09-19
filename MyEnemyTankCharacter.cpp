// Fill out your copyright notice in the Description page of Project Settings.


#include "MyEnemyTankCharacter.h"
#include "MyTankCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

void AMyEnemyTankCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (InFireRange())
	{
		RotateTurret(MyTank->GetActorLocation());

	}
}

void AMyEnemyTankCharacter::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}

void AMyEnemyTankCharacter::BeginPlay()
{
	Super::BeginPlay();
	MyTank = Cast<AMyTankCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &AMyEnemyTankCharacter::CheckFireCondition, FireRate, true);
}

void AMyEnemyTankCharacter::CheckFireCondition()
{
	if (MyTank && InFireRange() && MyTank->bAlive)
	{
		Fire();
	}
}

bool AMyEnemyTankCharacter::InFireRange()
{
	if (MyTank)
	{
		float Distance = FVector::Dist(MyTank->GetActorLocation(), GetActorLocation());
		if (Distance <= FireRange)
		{
			return true;
		}
	}
	return false;
}

