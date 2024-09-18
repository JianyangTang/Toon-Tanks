// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AsyncLibrary.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API UAsyncLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	static void CustomDelay(UObject* WorldContextObject, FName FunctionName, float Duration = 2.f);
	
};
