// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TESTTASK_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AMyPlayerController();

	// Blueprint events
	UFUNCTION(BlueprintImplementableEvent, Category = "TestTask")
		void OnMinionEnter();

	UFUNCTION(BlueprintImplementableEvent, Category = "TestTask")
		void OnMinionLeft();

	UFUNCTION(BlueprintImplementableEvent, Category = "TestTask")
		void OnInteract(class AMinion* Minion);
};
