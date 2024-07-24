// Copyright (c) 2024 Talentum Games Ltd. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "PenguinsPieceBase.h"
#include "PenguinsPieceNeutral.h"
#include "GameFramework/Actor.h"
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Board", meta = (ClampMin = "1", ClampMax = "10"))
	float RowHeight = 3.f;

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void InitialiseBoard();

private:
	void InitialiseBoardFromState(UPenguinsBoardState* State);
	void CreateSlots(const UPenguinsBoardState* State);
	void SpawnSlot(const double X, const double Y, const double HexWidth,
	               const FAttachmentTransformRules& AttachRules);
	float CalculateHexWidth(const UPenguinsBoardState* State) const;
};
