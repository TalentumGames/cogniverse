// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tile.h"
#include "UObject/NoExportTypes.h"
#include "BoardState.generated.h"

UCLASS(BlueprintType)
class COGNIVERSE_API UBoardState : public UObject
{
	GENERATED_BODY()

public:
	UBoardState();

	UPROPERTY(BlueprintReadOnly)
	TArray<FTile> Tiles;

	TArray<int32> GenerateRandomStart() const;
	void ApplyStartingPositions(TArray<int32> Positions);

private:
	const TArray<int32> RowLengths = {4, 5, 6, 7, 6, 5, 4};

	void InitialiseBoard();
	int32 TotalTiles() const;

	FTile& GetTileAt(int32 Row, int32 Column);
	int32 GetIndexFromRowColumn(int32 Row, int32 Column) const;
	bool IsValidRowColumn(int32 Row, int32 Column) const;
};
