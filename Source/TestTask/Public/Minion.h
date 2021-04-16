// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyCharacter.h"
#include "ContainerClass.h"
#include "Minion.generated.h"

/**
 * 
 */
UCLASS()
class TESTTASK_API AMinion : public AMyCharacter
{
	GENERATED_BODY()
public:

	AMinion();

	UPROPERTY(EditAnywhere, Category = "TestTask")
		int32 TestVar;

	UFUNCTION(BlueprintCallable, Category = "TestTask")
		void MoveToClosestObjectOfType(EObjectType::Type ObjectType);
};
