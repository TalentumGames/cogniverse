// Copyright (c) 2024 Talentum Games Ltd. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "PenguinsTile.h"
#include "UObject/NoExportTypes.h"
#include "PenguinsBoardState.generated.h"

UCLASS(BlueprintType)
class COGNIVERSE_API UPenguinsBoardState : public UObject
{
	GENERATED_BODY()

public:
	UPenguinsBoardState();

	const TArray<int32> RowLengths = {4, 5, 6, 7, 6, 5, 4};

	UPROPERTY(BlueprintReadOnly)
	TArray<FPenguinsTile> Tiles;

	TArray<int32> GenerateRandomStart() const;
	void ApplyStartingPositions(TArray<int32> Positions);
	int32 LongestRowLength() const;

private:
	void InitialiseBoard();

	FPenguinsTile& GetTileAt(int32 Row, int32 Column);
	int32 GetIndexFromRowColumn(int32 Row, int32 Column) const;
	bool IsValidRowColumn(int32 Row, int32 Column) const;
};
