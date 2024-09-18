// Fill out your copyright notice in the Description page of Project Settings.


#include "AsyncLibrary.h"
#include "DelayAction.h"

void UAsyncLibrary::CustomDelay(UObject* WorldContextObject, FName FunctionName, float Duration /*= 2.f*/)
{
	if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
	{
		FLatentActionManager& LatentActionManager = World->GetLatentActionManager();
		FLatentActionInfo LatentInfo;
		LatentInfo.CallbackTarget = WorldContextObject;
		LatentInfo.ExecutionFunction = FunctionName;
		LatentInfo.Linkage = 0;
		LatentInfo.UUID = FMath::Rand();
		LatentActionManager.AddNewAction(WorldContextObject, LatentInfo.UUID, new FDelayAction(5, LatentInfo));

	}
}
