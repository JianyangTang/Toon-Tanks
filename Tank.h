// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()
public:
	ATank();
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void HandleDestruction();
	class AToonTanksPlayerController* GetTankPlayerController() const { return TankPlayController; }
	bool bAlive = true;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void ActionControl_MoveForward(const FInputActionValue &value);
	void ActionControl_Turn(const FInputActionValue &value);
	void ActionControl_RotateTurretYaw(const FInputActionValue &value);
	void ActionControl_Fire(const FInputActionValue& value);
	void ActionControl_RotateTurretPitch(const FInputActionValue& value);
	void CallRotateTurret();
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CPP Components", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CPP Components", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera;
	UPROPERTY(EditAnywhere, Category = "Move")
	float TurnSpeed = 100;
	class AToonTanksPlayerController* TankPlayController;
	float RotationRate = 100;
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputMappingContext> IMC_Default;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputAction> IA_MoveForward;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputAction> IA_Turn;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputAction> IA_RotateTurretYaw;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputAction> IA_RotateTurretPitch;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputAction> IA_Fire;
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere)
	float MaxRange = 10000000;
};
