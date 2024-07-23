// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tile.h"
#include "UObject/NoExportTypes.h"
#include "BoardState.generated.h"

UCLASS()
class COGNIVERSE_API UBoardState : public UObject
{
	GENERATED_BODY()

public:
	UBoardState();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(BlueprintReadOnly, Replicated)
	TArray<FTile> Tiles;

	virtual bool IsSupportedForNetworking() const override
	{
		return true;
	}

private:
	const TArray<int32> RowLengths = {4, 5, 6, 7, 6, 5, 4};

	void InitialiseBoard();
	void GenerateRandomStart();
	int32 TotalTiles() const;

	FTile& GetTileAt(int32 Row, int32 Column);
	int32 GetIndexFromRowColumn(int32 Row, int32 Column) const;
	bool IsValidRowColumn(int32 Row, int32 Column) const;
};
