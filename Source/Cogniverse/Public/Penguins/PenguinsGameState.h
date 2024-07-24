// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "State/PenguinsBoardState.h"
#include "PenguinsGameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBoardInitialised);

UCLASS()
class COGNIVERSE_API APenguinsGameState : public AGameState
{
	GENERATED_BODY()

public:
	APenguinsGameState();
	virtual void PreInitializeComponents() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TObjectPtr<UPenguinsBoardState> Board;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_StartingPositionsAssigned)
	TArray<int32> StartingPositions;

	UFUNCTION(BlueprintCallable)
	void CreateStartingPositions();

	UFUNCTION()
	void OnRep_StartingPositionsAssigned() const;

	UPROPERTY(BlueprintAssignable, Category = "Game Events")
	FOnBoardInitialised OnBoardInitialised;
};
