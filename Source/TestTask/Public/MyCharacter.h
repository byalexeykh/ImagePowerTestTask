// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

UCLASS()
class TESTTASK_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// components
	class UCameraComponent* CameraComp;
	class UStaticMeshComponent* ChararcterMeshComp;
	class UStaticMeshComponent* DirectionMeshComp;

private:	

	// input
	void MoveForward(float value);
	void MoveRight(float value);
	void Turn(float value);
	void LookUp(float value);
	void Interact();
	void SpawnMinion();

	// gameplay
	bool bCanInteract;
	TArray<class AMinion*> Minions;
	UClass* MinionBlueprintClassRef;
	// Linetrace
	FHitResult Hit;
	FCollisionQueryParams Params;
};
