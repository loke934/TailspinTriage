// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GP4_StatTrackingSubsystem.h"
#include "GP4_MvpsLookUp.generated.h"

class UGP4_MvpData;
UCLASS(BlueprintType)
class FG21FT_GP4_TEAM05_API UGP4_MvpsLookUp : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<EMVPS, UGP4_MvpData*> MvpsLookUp;
	
};
