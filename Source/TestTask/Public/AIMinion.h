// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ContainerClass.h"
#include "AIMinion.generated.h"

/**
 * 
 */
UCLASS()
class TESTTASK_API AAIMinion : public AAIController
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "TestTask")
		void MoveTo(EObjectType::Type TypeOfObjectToMoveTo);

protected:
	virtual void OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result) override;

	AContainerClass* NeededContainer;
};
