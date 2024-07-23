// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "State/BoardState.h"
#include "PenguinsGameState.generated.h"

UCLASS()
class COGNIVERSE_API APenguinsGameState : public AGameState
{
	GENERATED_BODY()

public:
	APenguinsGameState();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(BlueprintReadOnly, Replicated, ReplicatedUsing=OnRep_Board)
	TObjectPtr<UBoardState> Board;

	UFUNCTION()
	void OnRep_Board();
};
