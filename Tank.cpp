// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanksPlayerController.h"
ATank::ATank()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Floating Pawn Movement"));
}
void ATank::BeginPlay()
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

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(IA_MoveForward, ETriggerEvent::Triggered, this, &ATank::ActionControl_MoveForward);
		EnhancedInputComponent->BindAction(IA_RotateTurretYaw, ETriggerEvent::Triggered, this, &ATank::ActionControl_RotateTurretYaw);
		EnhancedInputComponent->BindAction(IA_RotateTurretPitch, ETriggerEvent::Triggered, this, &ATank::ActionControl_RotateTurretPitch);
		EnhancedInputComponent->BindAction(IA_Turn, ETriggerEvent::Triggered, this, &ATank::ActionControl_Turn);
		EnhancedInputComponent->BindAction(IA_Fire, ETriggerEvent::Started, this, &ATank::ActionControl_Fire);
	}
}

void ATank::HandleDestruction()
{
	Super::HandleDestruction();
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
	bAlive = false;
}

void ATank::ActionControl_MoveForward(const FInputActionValue &value)
{
	AddMovementInput(GetBaseMesh()->GetForwardVector(), value.GetMagnitude() * MoveSpeed * GetWorld()->GetDeltaSeconds(),true);

}

void ATank::ActionControl_Turn(const FInputActionValue &value)
{
	FRotator DeltaRotation = FRotator::ZeroRotator;
	DeltaRotation.Yaw = - TurnSpeed * value.GetMagnitude() * UGameplayStatics::GetWorldDeltaSeconds(this);
	GetBaseMesh()->SetWorldRotation(GetBaseMesh()->GetComponentRotation()+DeltaRotation,true);
	//GetBaseMesh()->AddLocalRotation(DeltaRotation, true);
}

void ATank::ActionControl_RotateTurretYaw(const FInputActionValue &value)
{
	AddControllerYawInput(value.GetMagnitude() * RotationRate * GetWorld()->GetDeltaSeconds());
	CallRotateTurret();
}

void ATank::ActionControl_Fire(const FInputActionValue& value)
{
	CallRotateTurret();
	Fire();
}

void ATank::ActionControl_RotateTurretPitch(const FInputActionValue& value)
{
	AddControllerPitchInput(value.GetMagnitude() * RotationRate * GetWorld()->GetDeltaSeconds());
	CallRotateTurret();
}

void ATank::CallRotateTurret()
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
			//DrawDebugPoint(GetWorld(), HitResult.Location, 20, FColor::Red, false,0.5);
			RotateTurret(HitResult.Location);
		}
	}
}

void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}
