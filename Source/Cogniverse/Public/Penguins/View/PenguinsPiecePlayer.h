// Copyright (c) 2024 Talentum Games Ltd. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Math/Color.h"
#include "Penguins/View/PenguinsPieceBase.h"
#include "PenguinsPiecePlayer.generated.h"

UCLASS()
class COGNIVERSE_API APenguinsPiecePlayer : public APenguinsPieceBase
{
	GENERATED_BODY()

public:
	APenguinsPiecePlayer();

	UPROPERTY(EditDefaultsOnly, Category = "Piece")
	FLinearColor YellowColour;

	UPROPERTY(EditDefaultsOnly, Category = "Piece")
	FLinearColor RedColour;

	void Init(EPenguinsSide Side, FIntVector2 Location);

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	EPenguinsSide Player;
};
