// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseTankCharacter.generated.h"

UCLASS()
class TOONTANKS_API ABaseTankCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseTankCharacter();
	UStaticMeshComponent* GetBaseMesh() { return BaseMesh; }
	UStaticMeshComponent* GetTurretMesh() { return TurretMesh; }
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void RotateTurret(FVector LookAtLocation);
	void Fire();
	void HandleDestruction();
private:
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

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
