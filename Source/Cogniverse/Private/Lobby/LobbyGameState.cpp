// Copyright (c) 2024 Talentum Games Ltd. All rights reserved.


#include "Lobby/LobbyGameState.h"

#include "GameFramework/PlayerState.h"

TArray<FString> ALobbyGameState::BuildPlayerNames()
{
	TArray<FString> PlayerNames;

	for (const auto Player : PlayerArray)
	{
		PlayerNames.Add(Player->GetPlayerName());
	}

	return PlayerNames;
}
