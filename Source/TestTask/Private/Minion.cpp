// Fill out your copyright notice in the Description page of Project Settings.


#include "Minion.h"
#include "AIMinion.h"
#include "Components/CapsuleComponent.h"
#include "ContainerClass.h"

AMinion::AMinion() {
	ChararcterMeshComp->SetCanEverAffectNavigation(false);
}

void AMinion::MoveToClosestObjectOfType(EObjectType::Type ObjectType)
{
	GetController<AAIMinion>()->MoveTo(ObjectType);
}
