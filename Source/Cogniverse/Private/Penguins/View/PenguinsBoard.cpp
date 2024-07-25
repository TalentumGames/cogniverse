// Copyright (c) 2024 Talentum Games Ltd. All rights reserved.

#include "Penguins/View/PenguinsBoard.h"

#include "MathUtil.h"
#include "Penguins/PenguinsGameState.h"

APenguinsBoard::APenguinsBoard()
{
	PrimaryActorTick.bCanEverTick = false;
}

void APenguinsBoard::BeginPlay()
{
	Super::BeginPlay();
}

void APenguinsBoard::InitialiseBoard()
{
	if (const auto World = GetWorld())
	{
		const APenguinsGameState* GameState = Cast<APenguinsGameState>(World->GetGameState());
		if (GameState && GameState->Board)
		{
			UE_LOG(LogTemp, Warning, TEXT("Setting up initial board state with starting positions"))
			InitialiseBoardFromState(GameState->Board);
		}
	}
}

void APenguinsBoard::HandleAction(const FPenguinsAction Action)
{
	if (Action.FromX == -1 && Action.FromY == -1)
	{
		PlacePlayerPiece(Action);
	}
	else
	{
		MovePlayerPiece(Action);
	}
}

void APenguinsBoard::InitialiseBoardFromState(const UPenguinsBoardState* State)
{
	HexWidth = CalculateHexWidth(State);
	CreateSlots(State);
	PlaceNeutralPieces(State);
}

void APenguinsBoard::CreateSlots(const UPenguinsBoardState* State)
{
	const FAttachmentTransformRules AttachRules(EAttachmentRule::KeepRelative, false);
	for (const auto Tile : State->Tiles)
	{
		const int32 Row = Tile.Location.X;
		const int32 Col = Tile.Location.Y;
		const FVector2d Location2D = CalculateTileLocation(State, Tile);
		const FVector Location = FVector(Location2D.X, Location2D.Y, 0);
		if (const auto Slot = SpawnPiece(SlotClass, Location, AttachRules))
		{
			Slot->BoardLocation = FInt32Vector2(Row, Col);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to spawn slot (%d, %d)"), Row, Col);
		}
	}
}

void APenguinsBoard::PlaceNeutralPieces(const UPenguinsBoardState* State)
{
	const FAttachmentTransformRules AttachRules(EAttachmentRule::KeepRelative, false);
	for (const auto Tile : State->Tiles)
	{
		switch (Tile.State)
		{
		case EPenguinsTileState::Unoccupied:
			break;
		case EPenguinsTileState::Neutral:
			{
				const int32 Row = Tile.Location.X;
				const int32 Col = Tile.Location.Y;
				const FVector2d Location2D = CalculateTileLocation(State, Tile);
				const FVector Location = FVector(Location2D.X, Location2D.Y, 10);
				if (const auto Piece = SpawnPiece(NeutralPieceClass, Location, AttachRules))
				{
					Piece->BoardLocation = FInt32Vector2(Row, Col);
				}
				else
				{
					UE_LOG(LogTemp, Error, TEXT("Failed to spawn neutral piece (%d, %d)"), Row, Col);
				}
				break;
			}
		default:
			UE_LOG(LogTemp, Error, TEXT("Unexpected tile state"))
		}
	}
}

TObjectPtr<APenguinsPieceBase> APenguinsBoard::SpawnPiece(TSubclassOf<APenguinsPieceBase> PieceClass,
                                                          const FVector& Location,
                                                          const FAttachmentTransformRules& AttachRules)
{
	APenguinsPieceBase* Piece = GetWorld()->SpawnActor<
		APenguinsPieceBase>(PieceClass, Location, FRotator::ZeroRotator);

	if (Piece)
	{
		Piece->SetActorRotation(FRotator(0, 0, -90));
		Piece->SetSize(HexWidth * 0.9f);
		Piece->AttachToActor(this, AttachRules);
		return Piece;
	}
	return nullptr;
}

/**
 * Calculate the width of hexagonal slots. This needs to be computed based
 * on the overall size of the board as the board itself should remain a regular hexagon.
 * 
 * @return The width slots should occupy on the board.
 */
float APenguinsBoard::CalculateHexWidth(const UPenguinsBoardState* State) const
{
	const float BoardHeight = RowHeight + RowHeight * 0.75f * (State->RowLengths.Num() - 1);
	const float DesiredBoardWidth = BoardHeight * 2 / TMathUtil<float>::Sqrt(3.f);

	return DesiredBoardWidth / State->LongestRowLength();
}

FVector2d APenguinsBoard::CalculateTileLocation(const UPenguinsBoardState* State, const FPenguinsTile Tile) const
{
	// the actual distance between rows, which is smaller than the height due to the hexagons touching
	const float RowDistance = RowHeight * 0.75f;

	const int32 Row = Tile.Location.X;
	const int32 RowLength = State->RowLengths[Row];

	const float Y = (State->RowLengths.Num() / 2 - Row) * RowDistance;
	const float XOffset = -(RowLength - 1) * HexWidth / 2;
	const float X = XOffset + Tile.Location.Y * HexWidth;

	return FVector2d(X, Y);
}

void APenguinsBoard::PlacePlayerPiece(const FPenguinsAction& Action)
{
	const APenguinsGameState* GameState = Cast<APenguinsGameState>(GetWorld()->GetGameState());
	if (GameState && GameState->Board)
	{
		// TODO: a lot of repetition here
		const FAttachmentTransformRules AttachRules(EAttachmentRule::KeepRelative, false);
		const int32 Row = Action.ToX;
		const int32 Col = Action.ToY;
		const auto Tile = GameState->Board->GetTileAt(Row, Col);
		const FVector2d Location2D = CalculateTileLocation(GameState->Board, Tile);
		const FVector Location = FVector(Location2D.X, Location2D.Y, 10);

		if (const auto Piece = SpawnPiece(PlayerPieceClass, Location, AttachRules))
		{
			if (const auto PlayerPiece = Cast<APenguinsPiecePlayer>(Piece))
			{
				PlayerPiece->Init(Action.Player, FIntVector2(Row, Col));
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to spawn player piece (%d, %d)"), Row, Col);
		}
	}
}

void APenguinsBoard::MovePlayerPiece(FPenguinsAction Action)
{
	// TODO: implement piece movement
}
