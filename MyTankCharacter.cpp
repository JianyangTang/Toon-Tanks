// Fill out your copyright notice in the Description page of Project Settings.


#include "MyTankCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanksPlayerController.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetMathLibrary.h"

AMyTankCharacter::AMyTankCharacter()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	GetBaseMesh()->SetCollisionResponseToChannel(ECC_GameTraceChannel1,ECR_Ignore);
	GetTurretMesh()->SetCollisionResponseToChannel(ECC_GameTraceChannel1,ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_GameTraceChannel1,ECR_Ignore);
}

void AMyTankCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(IA_MoveForward, ETriggerEvent::Triggered, this, &AMyTankCharacter::ActionControl_MoveForward);
		EnhancedInputComponent->BindAction(IA_RotateTurretYaw, ETriggerEvent::Triggered, this, &AMyTankCharacter::ActionControl_RotateTurretYaw);
		EnhancedInputComponent->BindAction(IA_RotateTurretPitch, ETriggerEvent::Triggered, this, &AMyTankCharacter::ActionControl_RotateTurretPitch);
		EnhancedInputComponent->BindAction(IA_Turn, ETriggerEvent::Triggered, this, &AMyTankCharacter::ActionControl_Turn);
		EnhancedInputComponent->BindAction(IA_Fire, ETriggerEvent::Started, this, &AMyTankCharacter::ActionControl_Fire);
	}
}

void AMyTankCharacter::HandleDestruction()
{
	Super::HandleDestruction();
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
	bAlive = false;
}

void AMyTankCharacter::BeginPlay()
{
	Super::BeginPlay();
	TankPlayController = Cast<AToonTanksPlayerController>(GetController());
	if (TankPlayController)
	{
		if (UEnhancedInputLocalPlayerSubsystem* EnhancedSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(TankPlayController->GetLocalPlayer()))
		{
			EnhancedSubsystem->AddMappingContext(IMC_Default, 0);
		}
	}
}

void AMyTankCharacter::ActionControl_MoveForward(const FInputActionValue& value)
{
	FRotator ControlRotation = GetControlRotation();
	FVector ForwardVector = UKismetMathLibrary::GetForwardVector(FRotator(
		0,
		ControlRotation.Yaw,
		0));
	
	AddMovementInput(ForwardVector,
		value.GetMagnitude() * MoveSpeed * GetWorld()->GetDeltaSeconds(),true);
	RotateBase();

}

void AMyTankCharacter::ActionControl_Turn(const FInputActionValue& value)
{
	// FRotator DeltaRotation = FRotator::ZeroRotator;
	// DeltaRotation.Yaw = - TurnSpeed * value.GetMagnitude() * UGameplayStatics::GetWorldDeltaSeconds(this);
	// GetBaseMesh()->SetWorldRotation(GetBaseMesh()->GetComponentRotation()+DeltaRotation,true);
	FRotator ControlRotation = GetControlRotation();
	FVector RightVector = UKismetMathLibrary::GetRightVector(FRotator(
		0,
		ControlRotation.Yaw,
		ControlRotation.Roll));
	AddMovementInput(RightVector, value.GetMagnitude() * GetWorld()->GetDeltaSeconds() * TurnSpeed, true);
	RotateBase();
}

void AMyTankCharacter::ActionControl_RotateTurretYaw(const FInputActionValue& value)
{
	AddControllerYawInput(value.GetMagnitude() * RotationRate * GetWorld()->GetDeltaSeconds());
}

void AMyTankCharacter::ActionControl_Fire(const FInputActionValue& value)
{
	Fire();
}

void AMyTankCharacter::ActionControl_RotateTurretPitch(const FInputActionValue& value)
{
	AddControllerPitchInput(value.GetMagnitude() * RotationRate * GetWorld()->GetDeltaSeconds());
}

void AMyTankCharacter::CallRotateTurret()
{
	if (TankPlayController)
	{
		FHitResult HitResult;
		FVector VP_Location;
		FRotator VP_Rotation;
		TankPlayController->GetPlayerViewPoint(VP_Location, VP_Rotation);
		FVector VP_EndLocation = VP_Location + VP_Rotation.Vector() * MaxRange;
		bool bSuccess = GetWorld()->LineTraceSingleByChannel(HitResult,
			VP_Location,
			VP_EndLocation,
			ECollisionChannel::ECC_GameTraceChannel1);
		if (bSuccess)
		{
			RotateTurret(HitResult.Location);
		}
	}
}

void AMyTankCharacter::RotateBase()
{
	GetBaseMesh()->SetWorldRotation(UKismetMathLibrary::Conv_VectorToRotator(GetVelocity()));
}

void AMyTankCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CallRotateTurret();

}
