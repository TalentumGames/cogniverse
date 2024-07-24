// Copyright (c) 2024 Talentum Games Ltd. All rights reserved.


#include "Penguins/PenguinsGameState.h"

#include "Net/UnrealNetwork.h"

APenguinsGameState::APenguinsGameState()
{
	Board = CreateDefaultSubobject<UPenguinsBoardState>(TEXT("BoardState"));
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
}

void APenguinsGameState::OnRep_StartingPositionsAssigned() const
{
	UE_LOG(LogTemp, Warning, TEXT("Applying starting positions on client"))
	Board->ApplyStartingPositions(StartingPositions);
	OnBoardInitialised.Broadcast();
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
