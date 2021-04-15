// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetCapsuleComponent()->SetCapsuleSize(40, 70);
	GetCapsuleComponent()->SetMobility(EComponentMobility::Movable);

	RootComponent = GetCapsuleComponent();

	CameraComp = CreateDefaultSubobject<UCameraComponent>("Camera");
	CameraComp->SetupAttachment(GetCapsuleComponent());
	CameraComp->bUsePawnControlRotation = true;
	CameraComp->SetRelativeLocation(FVector(0, 0, 70));
	CameraComp->SetFieldOfView(90);
	CameraComp->SetMobility(EComponentMobility::Movable);

	GetCharacterMovement()->MaxWalkSpeed = 500;

	ChararcterMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("CharacterMesh");
	ChararcterMeshComp->SetStaticMesh(ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Game/StarterContent/Shapes/Shape_NarrowCapsule.Shape_NarrowCapsule")).Object);
	ChararcterMeshComp->SetupAttachment(GetCapsuleComponent());
	ChararcterMeshComp->SetMobility(EComponentMobility::Movable);
	ChararcterMeshComp->bOwnerNoSee = true;
	ChararcterMeshComp->SetRelativeLocation(FVector(0, 0, -20));

	DirectionMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("DirectionMesh");
	DirectionMeshComp->SetStaticMesh(ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Game/StarterContent/Shapes/Shape_Cone.Shape_Cone")).Object);
	DirectionMeshComp->SetupAttachment(GetCapsuleComponent());
	DirectionMeshComp->SetMobility(EComponentMobility::Movable);
	DirectionMeshComp->bOwnerNoSee = true;
	DirectionMeshComp->SetRelativeLocation(FVector(0, 0, 30));
	DirectionMeshComp->SetRelativeRotation(FRotator(-90, 0, 0));
	DirectionMeshComp->SetWorldScale3D(FVector(0.5f));
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &AMyCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMyCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &AMyCharacter::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &AMyCharacter::LookUp);
}

void AMyCharacter::MoveForward(float value)
{
	AddMovementInput(GetActorForwardVector(), value);
}

void AMyCharacter::MoveRight(float value)
{
	AddMovementInput(GetActorRightVector(), value);
}

void AMyCharacter::Turn(float value)
{
	AddControllerYawInput(value);
}

void AMyCharacter::LookUp(float value)
{
	AddControllerPitchInput(value);
}

