// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "MyCharacter.h"
#include "MyPlayerController.h"

AMyGameModeBase::AMyGameModeBase() {
	DefaultPawnClass = ConstructorHelpers::FObjectFinder<UClass>(TEXT("/Game/Blueprints/BP_MyCharacter.BP_MyCharacter_C")).Object;
	PlayerControllerClass = ConstructorHelpers::FObjectFinder<UClass>(TEXT("/Game/Blueprints/BP_MyPlayerController.BP_MyPlayerController_C")).Object;
}