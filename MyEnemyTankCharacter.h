// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseTankCharacter.h"
#include "MyEnemyTankCharacter.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AMyEnemyTankCharacter : public ABaseTankCharacter
{
	GENERATED_BODY()
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void HandleDestruction();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:
	class AMyTankCharacter* MyTank;
	UPROPERTY(EditAnywhere, Category = "Combat")
	float FireRange = 1000;
	FTimerHandle FireRateTimerHandle;
	float FireRate = 2.f;
	void CheckFireCondition();
	bool InFireRange();
};
