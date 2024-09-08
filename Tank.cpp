// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"

ATank::ATank()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}
void ATank::BeginPlay()
{
	Super::BeginPlay();
	PlayController = Cast<APlayerController>(GetController());
	if (PlayController)
	{
		if (UEnhancedInputLocalPlayerSubsystem* EnhancedSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayController->GetLocalPlayer()))
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
		EnhancedInputComponent->BindAction(IA_MoveForward, ETriggerEvent::Triggered, this, &ATank::Action_ControllerMoveForward);
		EnhancedInputComponent->BindAction(IA_RotateTurret, ETriggerEvent::Triggered, this, &ATank::Action_ControllerRotateTurret);
		EnhancedInputComponent->BindAction(IA_Turn, ETriggerEvent::Triggered, this, &ATank::Action_ControllerTurn);
		EnhancedInputComponent->BindAction(IA_Fire, ETriggerEvent::Started, this, &ATank::Action_ControllerFire);
	}
}
void ATank::Action_ControllerMoveForward(const FInputActionValue &value)
{
	FVector DeltaLocation = FVector::ZeroVector;
	DeltaLocation.X = MoveSpeed * value.GetMagnitude() * UGameplayStatics::GetWorldDeltaSeconds(this);
	AddActorLocalOffset(DeltaLocation, true);
}
void ATank::Action_ControllerTurn(const FInputActionValue &value)
{
	FRotator DeltaRotation = FRotator::ZeroRotator;
	DeltaRotation.Yaw = - TurnSpeed * value.GetMagnitude() * UGameplayStatics::GetWorldDeltaSeconds(this);
	AddActorLocalRotation(DeltaRotation, true);
}
void ATank::Action_ControllerRotateTurret(const FInputActionValue &value)
{
	if (PlayController)
	{
		FHitResult HitResult;
		PlayController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility,
			false,
			HitResult);
		RotateTurret(HitResult.ImpactPoint);

	}
}

void ATank::Action_ControllerFire(const FInputActionValue& value)
{
	Fire();
}

void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}
