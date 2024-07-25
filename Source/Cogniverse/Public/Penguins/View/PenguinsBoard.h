// Copyright (c) 2024 Talentum Games Ltd. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "PenguinsPieceBase.h"
#include "PenguinsPieceNeutral.h"
#include "PenguinsPiecePlayer.h"
#include "GameFramework/Actor.h"
#include "Penguins/State/PenguinsAction.h"
#include "Penguins/State/PenguinsBoardState.h"
#include "PenguinsBoard.generated.h"

UCLASS()
class COGNIVERSE_API APenguinsBoard : public AActor
{
	GENERATED_BODY()

public:
	APenguinsBoard();

	UPROPERTY(EditDefaultsOnly, Category = "Board")
	TSubclassOf<APenguinsPieceBase> SlotClass;

	UPROPERTY(EditDefaultsOnly, Category = "Board")
	TSubclassOf<APenguinsPieceNeutral> NeutralPieceClass;

	UPROPERTY(EditDefaultsOnly, Category = "Board")
	TSubclassOf<APenguinsPiecePlayer> PlayerPieceClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Board", meta = (ClampMin = "1", ClampMax = "10"))
	float RowHeight = 3.f;

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void InitialiseBoard();

	UFUNCTION(BlueprintCallable)
	void HandleAction(FPenguinsAction Action);

private:
	void InitialiseBoardFromState(const UPenguinsBoardState* State);
	void CreateSlots(const UPenguinsBoardState* State);
	void PlaceNeutralPieces(const UPenguinsBoardState* State);
	TObjectPtr<APenguinsPieceBase> SpawnPiece(TSubclassOf<APenguinsPieceBase> PieceClass,
	                                          const FVector& Location,
	                                          const FAttachmentTransformRules& AttachRules);

	float CalculateHexWidth(const UPenguinsBoardState* State) const;
	float HexWidth;

	FVector2d CalculateTileLocation(const UPenguinsBoardState* State, FPenguinsTile Tile) const;

	void PlacePlayerPiece(const FPenguinsAction& Action);
	void MovePlayerPiece(FPenguinsAction Action);
};
