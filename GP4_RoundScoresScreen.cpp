// Fill out your copyright notice in the Description page of Project Settings.


#include "GP4_RoundScoresScreen.h"
#include "FG21FT_GP4_Team05/Public/GP4_StatTrackingSubsystem.h"
#include "GP4_GameInstance.h"
#include "Kismet/GameplayStatics.h"


void UGP4_RoundScoresScreen::NativeConstruct()
{
	Super::NativeConstruct();
	UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(GetWorld());
	UGP4_GameInstance* MyGameInstance = Cast<UGP4_GameInstance>(GameInstance);
	StatTrackingSystem = MyGameInstance->GetSubsystem<UGP4_StatTrackingSubsystem>(MyGameInstance);
}





