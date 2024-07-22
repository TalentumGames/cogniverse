// Fill out your copyright notice in the Description page of Project Settings.


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
