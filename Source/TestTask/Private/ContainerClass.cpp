// Fill out your copyright notice in the Description page of Project Settings.


#include "ContainerClass.h"

// Sets default values
AContainerClass::AContainerClass()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	MeshComp->SetStaticMesh(ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Game/StarterContent/Shapes/Shape_QuadPyramid.Shape_QuadPyramid")).Object);

	RootComponent = MeshComp;
}
