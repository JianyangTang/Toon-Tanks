// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Field/FieldSystemActor.h"
#include "BrickFractureField.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ABrickFractureField : public AFieldSystemActor
{
	GENERATED_BODY()
	
	
public:
	ABrickFractureField();
	void InitializeField();
	UFUNCTION()
	void DelayFinish();
private:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CPP Components", meta = (AllowPrivateAccess = "true"))
	class UFieldSystemComponent* FieldSystem;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CPP Components", meta = (AllowPrivateAccess = "true"))
	class URadialFalloff* RadialFalloff;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CPP Components", meta = (AllowPrivateAccess = "true"))
	class URadialVector* RadialVector;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CPP Components", meta = (AllowPrivateAccess = "true"))
	class USphereComponent* SphereCollision;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CPP Components", meta = (AllowPrivateAccess = "true"))
	class UCullingField* CullingField;
	FTimerHandle ExistTimerHandle;
	UPROPERTY(EditAnywhere)
	float RadialSpeed = 500;
	float FieldRadius = 100;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
