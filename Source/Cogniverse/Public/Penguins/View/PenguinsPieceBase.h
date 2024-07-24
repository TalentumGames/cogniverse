// Copyright (c) 2024 Talentum Games Ltd. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "PaperSpriteComponent.h"
#include "GameFramework/Actor.h"
#include "PenguinsPieceBase.generated.h"

UCLASS()
class COGNIVERSE_API APenguinsPieceBase : public AActor
{
	GENERATED_BODY()

public:
	APenguinsPieceBase();

	UFUNCTION(BlueprintCallable, Category = "Properties")
	void SetSize(float NewSize);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UPaperSpriteComponent> SpriteComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties")
	float Size;
};
