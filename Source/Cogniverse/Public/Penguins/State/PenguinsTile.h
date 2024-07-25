// Copyright (c) 2024 Talentum Games Ltd. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PenguinsTile.generated.h"

UENUM(BlueprintType)
enum class EPenguinsTileState : uint8
{
	Unoccupied UMETA(DisplayName = "Unoccupied"),
	Neutral UMETA(DisplayName = "Neutral Piece"),
	Yellow UMETA(DisplayName = "Yellow"),
	Red UMETA(DisplayName = "Red")
};


USTRUCT(BlueprintType)
struct FPenguinsTile
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EPenguinsTileState State;

	UPROPERTY()
	FInt32Vector2 Location;

	FPenguinsTile() : State(EPenguinsTileState::Neutral), Location(FInt32Vector2(0, 0))
	{
	}
};
