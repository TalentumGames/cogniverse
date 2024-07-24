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
	Player1 UMETA(DisplayName = "Player 1"),
	Player2 UMETA(DisplayName = "Player 2")
};


USTRUCT(BlueprintType)
struct FPenguinsTile
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EPenguinsTileState State;

	FPenguinsTile() : State(EPenguinsTileState::Neutral)
	{
	}
};
