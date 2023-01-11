// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GP4_MvpData.generated.h"

UCLASS()
class FG21FT_GP4_TEAM05_API UGP4_MvpData : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	FString Title;
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	FString Text;
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	bool bBonus;
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	bool bDeduction;
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	int Amount;
	
};
