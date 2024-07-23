// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Tile.generated.h"

UENUM(BlueprintType)
enum class ETileState : uint8
{
	Unoccupied UMETA(DisplayName = "Unoccupied"),
	Neutral UMETA(DisplayName = "Neutral Piece"),
	Player1 UMETA(DisplayName = "Player 1"),
	Player2 UMETA(DisplayName = "Player 2")
};


USTRUCT(BlueprintType)
struct FTile
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ETileState State;

	FTile() : State(ETileState::Neutral)
	{
	}
};
