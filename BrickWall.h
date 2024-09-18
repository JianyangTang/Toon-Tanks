// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "BrickWall.generated.h"

UCLASS()
class TOONTANKS_API ABrickWall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABrickWall();
	void HandleDestruction();
	void DelayFinish();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CPP Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UGeometryCollectionComponent> GeometryCollection;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CPP Components", meta = (AllowPrivateAccess = "true"))
	class UHealthComponent* HealthComponent;
	UPROPERTY(EditAnywhere, Category = "CPP Components")
	TSubclassOf<class ABrickFractureField> BrickFractureFieldClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CPP Components", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* BoxMesh;
	FTimeline TransparentTimeline;
	UPROPERTY(EditAnywhere, Category = "CPP Components")
	UCurveFloat* TransparentFloatCurve;
	UFUNCTION()
	void TransparentTimelineFloatReturn(float Value);
	UFUNCTION()
	void TransparentTimelineFinished();
	float OpacityValue;
};
