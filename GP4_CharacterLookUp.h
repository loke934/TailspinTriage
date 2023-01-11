// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GP4_CharacterData.h"
#include "Engine/DataAsset.h"
#include "GP4_CharacterLookUp.generated.h"

UCLASS(BlueprintType)
class FG21FT_GP4_TEAM05_API UGP4_CharacterLookUp : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<int,UGP4_CharacterData*> CharacterLookUp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int TestVar;
	
};
