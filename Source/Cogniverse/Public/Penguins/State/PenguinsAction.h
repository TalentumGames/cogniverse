// Copyright (c) 2024 Talentum Games Ltd. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Penguins/PenguinsPlayerState.h"
#include "PenguinsAction.generated.h"

USTRUCT(BlueprintType)
struct FPenguinsAction
{
	GENERATED_BODY()

	FPenguinsAction();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EPenguinsSide Player = EPenguinsSide::Unassigned;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 FromX = -1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 FromY = -1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 ToX = -1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 ToY = -1;
};
