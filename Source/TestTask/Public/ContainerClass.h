// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ContainerClass.generated.h"

UENUM(BlueprintType)
enum class ObjectType : uint8 {
	Cube,
	Cylinder,
	Pyramid,
	Sphere,
	Torus,
	Wedge
};

UCLASS()
class TESTTASK_API AContainerClass : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AContainerClass();

	UPROPERTY(EditAnywhere, Category = "TestTask")
		ObjectType NeededObject;

private:
	UStaticMeshComponent* MeshComp;
};
