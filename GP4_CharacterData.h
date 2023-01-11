// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GP4_CharacterData.generated.h"

UCLASS(BlueprintType)
class FG21FT_GP4_TEAM05_API UGP4_CharacterData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* Texture = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UMaterial* PlayerColorMaterial = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UMaterial* GoalMaterial = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FLinearColor Color;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UMaterial* TeamMaterial = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* Icon = nullptr;
};
