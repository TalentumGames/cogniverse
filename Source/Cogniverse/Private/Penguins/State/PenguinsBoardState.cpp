// Copyright (c) 2024 Talentum Games Ltd. All rights reserved.


#include "Penguins/State/PenguinsBoardState.h"

#include "Net/UnrealNetwork.h"

UPenguinsBoardState::UPenguinsBoardState()
{
	InitialiseBoard();
}

void UPenguinsBoardState::InitialiseBoard()
{
	for (int32 Row = 0; Row < RowLengths.Num(); ++Row)
	{
		for (int32 Col = 0; Col < RowLengths[Row]; ++Col)
		{
			auto Tile = FPenguinsTile();
			Tile.Location = FInt32Vector2(Row, Col);
			Tiles.Add(Tile);
		}
	}
}

TArray<int32> UPenguinsBoardState::GenerateRandomStart() const
{
	// TODO: would some shuffling algorithm be more appropriate?
	TArray<int32> UnoccupiedIndices;
	const int32 TileCount = Tiles.Num();

	while (UnoccupiedIndices.Num() < PiecesPerPlayer * 2)
	{
		int32 RandomIndex = FMath::RandRange(0, TileCount - 1);
		if (!UnoccupiedIndices.Contains(RandomIndex))
		{
			UnoccupiedIndices.Add(RandomIndex);
		}
	}

	return UnoccupiedIndices;
}

void UPenguinsBoardState::ApplyStartingPositions(TArray<int32> Positions)
{
	for (int32 Position : Positions)
	{
		Tiles[Position].State = EPenguinsTileState::Unoccupied;
	}
}

int32 UPenguinsBoardState::LongestRowLength() const
{
	int32 Max = 0;
	for (const int32 RowLength : RowLengths)
	{
		if (RowLength > Max)
		{
			Max = RowLength;
		}
	}

	return Max;
}

FPenguinsTile& UPenguinsBoardState::GetTileAt(int32 Row, int32 Column)
{
	check(IsValidRowColumn(Row, Column));
	int32 Index = GetIndexFromRowColumn(Row, Column);
	return Tiles[Index];
}

void UPenguinsBoardState::AssignToPlayer(const EPenguinsSide Player, const int32 Row, const int32 Col)
{
	switch (Player)
	{
	case EPenguinsSide::Yellow:
		{
			GetTileAt(Row, Col).State = EPenguinsTileState::Yellow;
			break;
		}
	case EPenguinsSide::Red:
		{
			GetTileAt(Row, Col).State = EPenguinsTileState::Red;
			break;
		}
	case EPenguinsSide::Unassigned:
		{
			UE_LOG(LogTemp, Error, TEXT("Attempted to assign tile to invalid player"))
			break;
		}
	}
}

void UPenguinsBoardState::Clear(const int32 Row, const int32 Col)
{
	GetTileAt(Row, Col).State = EPenguinsTileState::Unoccupied;
}

bool UPenguinsBoardState::IsReadyForMovement()
{
	int32 NumPlayerPieces = 0;
	for (const auto Tile : Tiles)
	{
		if (Tile.State == EPenguinsTileState::Red || Tile.State == EPenguinsTileState::Yellow)
		{
			NumPlayerPieces++;
		}
	}

	return NumPlayerPieces == PiecesPerPlayer * 2;
}

int32 UPenguinsBoardState::GetIndexFromRowColumn(int32 Row, int32 Column) const
{
	int32 Index = 0;
	for (int32 i = 0; i < Row; ++i)
	{
		Index += RowLengths[i];
	}
	return Index + Column;
}

bool UPenguinsBoardState::IsValidRowColumn(const int32 Row, const int32 Column) const
{
	return Row >= 0 && Row < RowLengths.Num() && Column >= 0 && Column < RowLengths[Row];
}
