// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DrawDebugHelpers.h"
#include "Minion.h"
#include "MyPlayerController.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bUseControllerRotationPitch = true;
	bUseControllerRotationRoll = true;
	bUseControllerRotationYaw = true;
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

	// Linetrace settings
	Params.AddIgnoredActor(this);
	Params.bTraceComplex = true;

	// Getting BP version of AMinion class 
	//ConstructorHelpers::FObjectFinder<UClass> MinionBP(TEXT("/Game/Blueprints/BP_Minion.BP_Minion_C"));  // =========================== //
	//if (MinionBP.Object != NULL) {																	   //		PROBLEM O KTÓRYM	  //
	//	MinionBlueprintClassRef = (UClass*)MinionBP.Object;												   //		CHODZIŁO W MAILU	  //
	//}																									   // =========================== //

	// default var values
	bCanInteract = false;
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	GetWorld()->LineTraceSingleByChannel(Hit, CameraComp->GetComponentLocation(), CameraComp->GetComponentLocation() + (GetControlRotation().Vector() * 600), ECollisionChannel::ECC_Visibility, Params);
	if (IsPlayerControlled()) {
		if (Hit.GetActor()) {
			if (Hit.GetActor()->IsA<AMinion>()) {
				GetController<AMyPlayerController>()->OnMinionEnter();
				bCanInteract = true;
			}
			else {
				GetController<AMyPlayerController>()->OnMinionLeft();
				bCanInteract = false;
			}
		}
		else {
			GetController<AMyPlayerController>()->OnMinionLeft();
			bCanInteract = false;
		}
	}
}

void AMyCharacter::SpawnMinion()
{
	if (Hit.GetActor()) {
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
		
		AMinion* m = GetWorld()->SpawnActor<AMinion>(/*MinionBlueprintClassRef, */Hit.ImpactPoint, FRotator::ZeroRotator, SpawnParams); // MinionBlueprintClassRef to reference do BP_Minion'u, ktory musiał pobierać FObjectFinder
		
		if (m) {
			Minions.Add(m);
			// A variable to make sure that spawns BP version of minion
			//UE_LOG(LogTemp, Warning, TEXT("TestVar: %i"), Minions[0]->TestVar);
		
			if (Minions.Num() >= 6) {
				Minions[0]->Destroy();
				Minions.RemoveAt(0, 1, true);
			}
		}
	}
}

void AMyCharacter::Interact()
{
	if (bCanInteract) {
		GetController<AMyPlayerController>()->OnInteract(Cast<AMinion>(Hit.GetActor()));
	}
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &AMyCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMyCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &AMyCharacter::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &AMyCharacter::LookUp);

	PlayerInputComponent->BindAction("SpawnMinion", IE_Pressed, this, &AMyCharacter::SpawnMinion);
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AMyCharacter::Interact);
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
	AddControllerPitchInput(-1 * value);
}
