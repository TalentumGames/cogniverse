// Copyright (c) 2024 Talentum Games Ltd. All rights reserved.


#include "Penguins/PenguinsPlayerState.h"

#include "Net/UnrealNetwork.h"

APenguinsPlayerState::APenguinsPlayerState()
{
	bReplicates = true;
	bAlwaysRelevant = true;
}

void APenguinsPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(APenguinsPlayerState, Side)
}

void APenguinsPlayerState::OnRep_Side()
{
	OnSideAssigned.Broadcast();
}

void APenguinsPlayerState::SetSideWithIndex(const int32 Idx)
{
	switch (Idx)
	{
	case 0:
		{
			Side = EPenguinsSide::Yellow;
			break;
		}
	case 1:
		{
			Side = EPenguinsSide::Red;
			break;
		}
	default:
		UE_LOG(LogTemp, Error, TEXT("Unexpected side index %d"), Idx);
	}
	OnRep_Side();
}

FString APenguinsPlayerState::GetSideString() const
{
	switch (Side)
	{
	case EPenguinsSide::Yellow:
		return "Yellow";
	case EPenguinsSide::Red:
		return "Red";
	case EPenguinsSide::Unassigned:
		return "Unassigned";
	}

	return "Unexpected";
}
