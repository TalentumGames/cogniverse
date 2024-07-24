// Copyright (c) 2024 Talentum Games Ltd. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "LobbyGameState.generated.h"

UCLASS()
class COGNIVERSE_API ALobbyGameState : public AGameStateBase
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintCallable)
	TArray<FString> BuildPlayerNames();
};
