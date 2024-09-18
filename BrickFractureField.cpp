// Fill out your copyright notice in the Description page of Project Settings.


#include "BrickFractureField.h"
#include "Field/FieldSystemComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/SphereComponent.h"
#include "AsyncLibrary.h"
#include "DelayAction.h"

ABrickFractureField::ABrickFractureField()
{
	FieldSystem = Cast<UFieldSystemComponent>(RootComponent);
	RadialFalloff = CreateDefaultSubobject<URadialFalloff>(TEXT("RadialFalloff"));
	RadialVector = CreateDefaultSubobject<URadialVector>(TEXT("RadialVector"));
	CullingField = CreateDefaultSubobject<UCullingField>(TEXT("CullingField"));
	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	SphereCollision->SetupAttachment(RootComponent);
	SphereCollision->SetSphereRadius(FieldRadius);
	
	
}

void ABrickFractureField::InitializeField()
{
	FieldRadius = SphereCollision->GetUnscaledSphereRadius();
	RadialFalloff->SetRadialFalloff(510000,
		0, 1, 0, FieldRadius, GetActorLocation(), EFieldFalloffType::Field_FallOff_None);
	FieldSystem = Cast<UFieldSystemComponent>(RootComponent);
	FieldSystem->ApplyPhysicsField(true,
		EFieldPhysicsType::Field_ExternalClusterStrain,
		nullptr,
		RadialFalloff
	);
	RadialVector->SetRadialVector(RadialSpeed, GetActorLocation());
	CullingField->SetCullingField(
		RadialFalloff,
		RadialVector,
		EFieldCullingOperationType::Field_Culling_Outside);
	FieldSystem->ApplyPhysicsField(true,
		EFieldPhysicsType::Field_LinearVelocity,
		nullptr,
		CullingField);
}

void ABrickFractureField::DelayFinish()
{
	Destroy();
}

void ABrickFractureField::BeginPlay()
{
	Super::BeginPlay();
	InitializeField();
	UAsyncLibrary::CustomDelay(this, TEXT("DelayFinish"), 0.1);
	
	
}
