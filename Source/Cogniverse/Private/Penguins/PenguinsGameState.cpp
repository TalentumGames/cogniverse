// Fill out your copyright notice in the Description page of Project Settings.


#include "Penguins/PenguinsGameState.h"

#include "Net/UnrealNetwork.h"

APenguinsGameState::APenguinsGameState()
{
	Board = CreateDefaultSubobject<UBoardState>(TEXT("BoardState"));
}

void APenguinsGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION(APenguinsGameState, Board, COND_InitialOnly);
}

void APenguinsGameState::OnRep_Board()
{
	UE_LOG(LogTemp, Warning, TEXT("Replicated board"));
}
