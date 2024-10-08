// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()
public:
	// Sets default values for this pawn's properties
	ABasePawn();
	UStaticMeshComponent* GetBaseMesh() { return BaseMesh; }
	UStaticMeshComponent* GetTurretMesh() { return TurretMesh; }
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void RotateTurret(FVector LookAtLocation);
	void Fire();
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CPP Components", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* BoxCollision;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CPP Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CPP Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* TurretMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CPP Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawnPoint;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CPP Components", meta = (AllowPrivateAccess = "true"))
	class UHealthComponent* HealthComponent;
	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<class AProjectile> ProjectileClass;
	UPROPERTY(EditAnywhere, Category = "Combat")
	class UParticleSystem* DeadParticles;
	UPROPERTY(EditAnywhere, Category = "Combat")
	class USoundBase* DeadSound;
	UPROPERTY(EditAnywhere, Category = "CPP Components")
	TSubclassOf<class UCameraShakeBase> DeathCameraShakeClass;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void HandleDestruction();

	
};
