// Fill out your copyright notice in the Description page of Project Settings.


#include "BrickWall.h"
#include "GeometryCollection/GeometryCollectionComponent.h"
#include "HealthComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/KismetMaterialLibrary.h"

// Sets default values
ABrickWall::ABrickWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GeometryCollection = CreateDefaultSubobject<UGeometryCollectionComponent>(TEXT("Geometry Collection"));
	RootComponent = GeometryCollection;
	GeometryCollection->SetCollisionResponseToChannel(ECollisionChannel::ECC_Destructible,
		ECollisionResponse::ECR_Ignore);
	GeometryCollection->SetSimulatePhysics(false);
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
	HealthComponent->SetMaxHealth(50);
	BoxMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Box Mesh"));
	BoxMesh->SetupAttachment(RootComponent);
	BoxMesh->SetHiddenInGame(true);
	BoxMesh->SetSimulatePhysics(true);
	BoxMesh->SetCollisionObjectType(ECollisionChannel::ECC_Destructible);
	BoxMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Destructible,
		ECollisionResponse::ECR_Ignore);

}

void ABrickWall::HandleDestruction()
{
/*	UE_LOG(LogTemp, Display, TEXT("Wall die"));*/
	BoxMesh->DestroyComponent();
	GeometryCollection->SetCollisionResponseToChannel(
		ECollisionChannel::ECC_WorldDynamic,
		ECollisionResponse::ECR_Ignore
	);
// 	BoxMesh->SetCollisionResponseToChannel(
// 		ECollisionChannel::ECC_WorldDynamic,
// 		ECollisionResponse::ECR_Ignore
// 	);
	GeometryCollection->SetSimulatePhysics(true);
	TransparentTimeline.Play();
}



// Called when the game starts or when spawned
void ABrickWall::BeginPlay()
{
	Super::BeginPlay();
	if (TransparentFloatCurve)
	{
		FOnTimelineFloat TransparentTimelineCallback;
		TransparentTimelineCallback.BindUFunction(this, FName("TransparentTimelineFloatReturn"));
		FOnTimelineEvent TransparentTimelineFinishedCallback;
		TransparentTimelineFinishedCallback.BindUFunction(this, FName("TransparentTimelineFinished"));
		TransparentTimeline.AddInterpFloat(TransparentFloatCurve, TransparentTimelineCallback);
		TransparentTimeline.SetTimelineFinishedFunc(TransparentTimelineFinishedCallback);
		TransparentTimeline.SetLooping(false);
	}
}

// Called every frame
void ABrickWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TransparentTimeline.TickTimeline(DeltaTime);
}

void ABrickWall::TransparentTimelineFloatReturn(float Value)
{
	GeometryCollection->SetScalarParameterValueOnMaterials("Opacity", Value);
}

void ABrickWall::TransparentTimelineFinished()
{
	Destroy();
}

