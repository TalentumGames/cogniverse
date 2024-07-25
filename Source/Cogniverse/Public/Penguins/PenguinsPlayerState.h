// Copyright (c) 2024 Talentum Games Ltd. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PenguinsPlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSideAssigned);

UENUM(BlueprintType)
enum class EPenguinsSide : uint8
{
	Yellow UMETA(DisplayName = "Yellow"),
	Red UMETA(DisplayName = "Red"),
	Unassigned UMETA(DisplayName = "Unassigned")
};

UCLASS()
class COGNIVERSE_API APenguinsPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	APenguinsPlayerState();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, ReplicatedUsing=OnRep_Side)
	EPenguinsSide Side = EPenguinsSide::Unassigned;

	UFUNCTION()
	void OnRep_Side();

	UFUNCTION(BlueprintCallable)
	void SetSideWithIndex(int32 Idx);

	FString GetSideString() const;

	UPROPERTY(BlueprintAssignable, Category = "Game Events")
	FOnSideAssigned OnSideAssigned;
};
