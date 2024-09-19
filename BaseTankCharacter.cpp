// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseTankCharacter.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile.h"
#include "HealthComponent.h"
#include "Camera/CameraShakeBase.h"
// Sets default values
ABaseTankCharacter::ABaseTankCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(GetMesh());
	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);
	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
}

// Called when the game starts or when spawned
void ABaseTankCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseTankCharacter::RotateTurret(FVector LookAtLocation)
{
	FVector ToTarget = LookAtLocation - TurretMesh->GetComponentLocation();
	TurretMesh->SetWorldRotation(ToTarget.Rotation());
}

void ABaseTankCharacter::Fire()
{
	if (ProjectileClass)
	{
			AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass,
        		ProjectileSpawnPoint->GetComponentLocation(),
        		ProjectileSpawnPoint->GetComponentRotation());
        	Projectile->SetOwner(this);
	}

}

void ABaseTankCharacter::HandleDestruction()
{
	if (DeadParticles)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this,
			DeadParticles,
			GetActorLocation(),
			GetActorRotation());
	}
	if (DeadSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this,
			DeadSound,
			GetActorLocation());
	}
	if (DeathCameraShakeClass)
	{
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(DeathCameraShakeClass);
	}
}

// Called every frame
void ABaseTankCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseTankCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

