// Copyright (c) 2024 Talentum Games Ltd. All rights reserved.


#include "Penguins/View/PenguinsPieceBase.h"

APenguinsPieceBase::APenguinsPieceBase()
{
	PrimaryActorTick.bCanEverTick = false;

	SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("SpriteComponent"));
	RootComponent = SpriteComponent;
}

void APenguinsPieceBase::SetSize(const float NewSize)
{
	Size = NewSize;

	if (SpriteComponent && SpriteComponent->GetSprite())
	{
		const float Scale = NewSize / 8.f;
		SpriteComponent->SetRelativeScale3D(FVector(Scale, Scale, Scale));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Attempting to resize slot but the sprite has not been set."))
	}
}

void APenguinsPieceBase::BeginPlay()
{
	Super::BeginPlay();
}
