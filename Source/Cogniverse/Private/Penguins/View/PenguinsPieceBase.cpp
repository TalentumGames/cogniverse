// Copyright (c) 2024 Talentum Games Ltd. All rights reserved.


#include "Penguins/View/PenguinsPieceBase.h"

#include "Penguins/PenguinsPlayerController.h"

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

FString APenguinsPieceBase::GetDebugName() const
{
	return FString::Printf(TEXT("%s (%d, %d)"), *GetClass()->GetName(), BoardLocation.X, BoardLocation.Y);
}

int32 APenguinsPieceBase::GetRow() const
{
	return BoardLocation.X;
}

int32 APenguinsPieceBase::GetColumn() const
{
	return BoardLocation.Y;
}

EPenguinsSide APenguinsPieceBase::GetMySide() const
{
	if (const auto PlayerController = Cast<APenguinsPlayerController>(GetWorld()->GetFirstPlayerController()))
	{
		return PlayerController->GetPlayerState<APenguinsPlayerState>()->Side;
	}

	UE_LOG(LogTemp, Error, TEXT("Couldn't get my side"))
	return EPenguinsSide::Unassigned;
}

void APenguinsPieceBase::BeginPlay()
{
	Super::BeginPlay();
}
