// Copyright (c) 2024 Talentum Games Ltd. All rights reserved.


#include "Penguins/PenguinsPlayerController.h"

#include "Camera/CameraActor.h"
#include "Kismet/GameplayStatics.h"

void APenguinsPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Find the camera in the level
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACameraActor::StaticClass(), FoundActors);

	if (FoundActors.Num() > 0)
	{
		// Set the view target to the first found camera
		SetViewTarget(FoundActors[0]);
		UE_LOG(LogTemp, Log, TEXT("Camera has been configured for view target."));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No eligible camera was found to set for view target."));
	}
}
