// Copyright (c) 2024 Talentum Games Ltd. All rights reserved.


#include "Penguins/PenguinsGameState.h"

#include "Net/UnrealNetwork.h"
#include "Penguins/State/PenguinsAction.h"

APenguinsGameState::APenguinsGameState()
{
	bReplicates = true;
	Board = nullptr;
}

void APenguinsGameState::PreInitializeComponents()
{
	Super::PreInitializeComponents();

	if (!Board)
	{
		Board = NewObject<UPenguinsBoardState>();
	}
}

void APenguinsGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(APenguinsGameState, StartingPositions);
	DOREPLIFETIME(APenguinsGameState, Actions);
}

void APenguinsGameState::OnRep_StartingPositionsAssigned()
{
	UE_LOG(LogTemp, Warning, TEXT("Applying starting positions on client"))
	Board->ApplyStartingPositions(StartingPositions);
	GamePhase = EPenguinsPhase::Placement;

	OnBoardInitialised.Broadcast();
}

void APenguinsGameState::OnRep_Actions()
{
	const FColor MessageColour = HasAuthority() ? FColor::Orange : FColor::Yellow;
	while (ActionMarker < Actions.Num())
	{
		ApplyAction(Actions[ActionMarker]);
		OnTurnEnded.Broadcast(Actions[ActionMarker]);
		auto Message = FString::Printf(
			TEXT("Turn ended (action=%d)"), ActionMarker);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, MessageColour, Message);
		ActionMarker++;
	}
}

void APenguinsGameState::AddAction(const FPenguinsAction& Action)
{
	if (HasAuthority())
	{
		Actions.Add(Action);
		OnRep_Actions();
	}
}

void APenguinsGameState::ApplyAction(const FPenguinsAction& Action)
{
	if (Action.FromX != -1 && Action.FromY != -1)
	{
		UE_LOG(LogTemp, Warning, TEXT("Moving piece"))
		Board->Clear(Action.FromX, Action.FromY);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Placing new piece"))
	}
	Board->AssignToPlayer(Action.Player, Action.ToX, Action.ToY);

	SwitchPlayer(Action.Player);
}

void APenguinsGameState::SwitchPlayer(const EPenguinsSide PreviousPlayer)
{
	if (PreviousPlayer == EPenguinsSide::Yellow)
	{
		ActivePlayer = EPenguinsSide::Red;
	}
	else
	{
		ActivePlayer = EPenguinsSide::Yellow;
	}
}

void APenguinsGameState::TransitionPhase()
{
	if (GamePhase == EPenguinsPhase::Placement && Board->IsReadyForMovement())
	{
		GamePhase = EPenguinsPhase::Movement;
	}
}

void APenguinsGameState::CreateStartingPositions()
{
	if (HasAuthority())
	{
		if (Board)
		{
			const auto Positions = Board->GenerateRandomStart();
			StartingPositions = Positions;
			OnRep_StartingPositionsAssigned();
		}
		else
		{
			UE_LOG(LogTemp, Warning,
			       TEXT("Creating starting positions, but board is null"))
		}
	}
}

bool APenguinsGameState::CanPlaceAt(const EPenguinsSide Player, const int32 Row, const int32 Col) const
{
	if (GamePhase == EPenguinsPhase::Placement && ActivePlayer == Player)
	{
		const auto TileState = Board->GetTileAt(Row, Col).State;
		return TileState == EPenguinsTileState::Unoccupied;
	}

	return false;
}

bool APenguinsGameState::PlaceAt(const EPenguinsSide Player, const int32 Row, const int32 Col)
{
	if (CanPlaceAt(Player, Row, Col))
	{
		FPenguinsAction Action = FPenguinsAction();
		Action.Player = Player;
		Action.ToX = Row;
		Action.ToY = Col;
		AddAction(Action);
		return true;
	}

	UE_LOG(LogTemp, Warning, TEXT("Cannot place piece at (%d, %d)"), Row, Col)
	return false;
}
