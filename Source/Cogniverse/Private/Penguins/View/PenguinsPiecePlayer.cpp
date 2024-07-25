// Copyright (c) 2024 Talentum Games Ltd. All rights reserved.


#include "Penguins/View/PenguinsPiecePlayer.h"

APenguinsPiecePlayer::APenguinsPiecePlayer() : Player(EPenguinsSide::Unassigned)
{
}

void APenguinsPiecePlayer::Init(const EPenguinsSide Side, const FIntVector2 Location)
{
	Player = Side;
	BoardLocation = Location;

	switch (Side)
	{
	case EPenguinsSide::Yellow:
		{
			SpriteComponent->SetSpriteColor(YellowColour);
			break;
		}
	case EPenguinsSide::Red:
		{
			SpriteComponent->SetSpriteColor(RedColour);
			break;
		}
	case EPenguinsSide::Unassigned:
		{
			UE_LOG(LogTemp, Error, TEXT("Unassigned side when initialising player piece"))
			break;
		}
	}
}
