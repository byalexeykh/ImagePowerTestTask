// Fill out your copyright notice in the Description page of Project Settings.


#include "AIMinion.h"
#include "EngineUtils.h"
#include "ContainerClass.h"

void AAIMinion::MoveTo(EObjectType::Type TypeOfObjectToMoveTo)
{
	TMap<float, AContainerClass*> ContainersOfNeededType;
	for (TActorIterator<AContainerClass> Container(GetWorld()); Container; ++Container) {
		if (Container->NeededObject == TypeOfObjectToMoveTo) {
			ContainersOfNeededType.Add(FVector::Dist(GetPawn()->GetActorLocation(), Container->GetActorLocation()), *Container);
		}
	}

	if (ContainersOfNeededType.Num() <= 0) {
		UE_LOG(LogTemp, Error, TEXT("There's no such object!"));
		return;
	}

	TArray<float> temp;
	ContainersOfNeededType.GenerateKeyArray(temp);

	float MinimalDist = temp[0];
	for (int i = 0; i <= temp.Num() - 1; i++) {
		if (MinimalDist > temp[i]) {
			MinimalDist = temp[i];
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("Dist to closest container: %f"), MinimalDist);
	NeededContainer = ContainersOfNeededType[MinimalDist];
	MoveToActor(NeededContainer, 5);
}

void AAIMinion::OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result)
{
	if (Result == EPathFollowingResult::Success) {
		UE_LOG(LogTemp, Warning, TEXT("%s successfully moved to %s"), *GetPawn()->GetName(), *NeededContainer->GetName());
	}
}
