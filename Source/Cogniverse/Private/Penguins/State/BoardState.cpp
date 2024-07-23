// Fill out your copyright notice in the Description page of Project Settings.


#include "Penguins/State/BoardState.h"

#include "Net/UnrealNetwork.h"

UBoardState::UBoardState()
{
	InitialiseBoard();
}

void UBoardState::InitialiseBoard()
{
	// sets all tiles to neutral
	Tiles.SetNum(TotalTiles(), []() { return FTile(); });
}

TArray<int32> UBoardState::GenerateRandomStart() const
{
	// TODO: would some shuffling algorithm be more appropriate?
	TArray<int32> UnoccupiedIndices;
	const int32 TileCount = TotalTiles();

	while (UnoccupiedIndices.Num() < 6)
	{
		int32 RandomIndex = FMath::RandRange(0, TileCount - 1);
		if (!UnoccupiedIndices.Contains(RandomIndex))
		{
			UnoccupiedIndices.Add(RandomIndex);
		}
	}

	return UnoccupiedIndices;
}

void UBoardState::ApplyStartingPositions(TArray<int32> Positions)
{
	for (int32 Position : Positions)
	{
		Tiles[Position].State = ETileState::Unoccupied;
	}
}

int32 UBoardState::TotalTiles() const
{
	int32 Total = 0;

	for (const int32 RowLength : RowLengths)
	{
		Total += RowLength;
	}

	return Total;
}

FTile& UBoardState::GetTileAt(int32 Row, int32 Column)
{
	check(IsValidRowColumn(Row, Column));
	int32 Index = GetIndexFromRowColumn(Row, Column);
	return Tiles[Index];
}

int32 UBoardState::GetIndexFromRowColumn(int32 Row, int32 Column) const
{
	int32 Index = 0;
	for (int32 i = 0; i < Row; ++i)
	{
		Index += RowLengths[i];
	}
	return Index + Column;
}

bool UBoardState::IsValidRowColumn(const int32 Row, const int32 Column) const
{
	return Row >= 0 && Row < RowLengths.Num() && Column >= 0 && Column < RowLengths[Row];
}
