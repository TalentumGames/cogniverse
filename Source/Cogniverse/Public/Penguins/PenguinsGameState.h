// Copyright (c) 2024 Talentum Games Ltd. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "PenguinsPlayerState.h"
#include "GameFramework/GameState.h"
#include "State/PenguinsAction.h"
#include "State/PenguinsBoardState.h"
#include "PenguinsGameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBoardInitialised);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTurnEnded, FPenguinsAction, Action);

UENUM(BlueprintType)
enum class EPenguinsPhase : uint8
{
	Setup UMETA(DisplayName = "Setup"),
	Placement UMETA(DisplayName = "Placement"),
	Movement UMETA(DisplayName = "Movement"),
};

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

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Actions)
	TArray<FPenguinsAction> Actions;

	UFUNCTION(BlueprintCallable)
	void CreateStartingPositions();

	UFUNCTION(BlueprintCallable)
	bool CanPlaceAt(const EPenguinsSide Player, const int32 Row, const int32 Col) const;

	UFUNCTION(BlueprintCallable)
	bool PlaceAt(const EPenguinsSide Player, const int32 Row, const int32 Col);

	UFUNCTION()
	void OnRep_StartingPositionsAssigned();

	UFUNCTION()
	void OnRep_Actions();

	UPROPERTY(BlueprintAssignable, Category = "Game Events")
	FOnBoardInitialised OnBoardInitialised;

	UPROPERTY(BlueprintAssignable, Category = "Game Events")
	FOnTurnEnded OnTurnEnded;

protected:
	EPenguinsSide ActivePlayer = EPenguinsSide::Yellow;
	EPenguinsPhase GamePhase = EPenguinsPhase::Setup;
	int32 ActionMarker = 0;

private:
	void AddAction(const FPenguinsAction& Action);
	void ApplyAction(const FPenguinsAction& Action);
	void SwitchPlayer(const EPenguinsSide PreviousPlayer);
	void TransitionPhase();
};
