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
		APenguinsGameState* GameState = Cast<APenguinsGameState>(World->GetGameState());
		if (GameState && GameState->Board)
		{
			UE_LOG(LogTemp, Warning, TEXT("Setting up initial board state with starting positions"))
			InitialiseBoardFromState(GameState->Board);
		}
	}
}

void APenguinsBoard::InitialiseBoardFromState(UPenguinsBoardState* State)
{
	CreateSlots(State);
}

void APenguinsBoard::CreateSlots(const UPenguinsBoardState* State)
{
	const FAttachmentTransformRules AttachRules(EAttachmentRule::KeepRelative, false);
	const float HexWidth = CalculateHexWidth(State);
	// the actual distance between rows, which is smaller than the height due to the hexagons touching
	const float RowDistance = RowHeight * 0.75f;
	const int32 NumberOfRows = State->RowLengths.Num();

	for (int32 Row = 0; Row < NumberOfRows; ++Row)
	{
		const int32 RowLength = State->RowLengths[Row];
		const float Y = (NumberOfRows / 2 - Row) * RowDistance;
		const float XOffset = -(RowLength - 1) * HexWidth / 2;

		for (int32 Col = 0; Col < RowLength; ++Col)
		{
			const float X = XOffset + Col * HexWidth;
			SpawnSlot(X, Y, HexWidth, AttachRules);
		}
	}
}

void APenguinsBoard::SpawnSlot(const double X, const double Y, const double HexWidth,
                               const FAttachmentTransformRules& AttachRules)
{
	const FVector Location(X, Y, 0);
	APenguinsPieceBase* NewSlot = GetWorld()->SpawnActor<
		APenguinsPieceBase>(SlotClass, Location, FRotator::ZeroRotator);

	if (NewSlot)
	{
		NewSlot->SetActorRotation(FRotator(0, 0, -90));
		NewSlot->SetSize(HexWidth * 0.9f);
		NewSlot->AttachToActor(this, AttachRules);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Failed to initialise slot at (%f, %f)."), X, Y);
	}
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
