#pragma once
#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GP4_StatTrackingSubsystem.generated.h"

UENUM(BlueprintType)
enum class EMVPS : uint8
{
	EMVPS_Altruist UMETA(DisplayName = "Altruist"),
	EMVPS_Saboteur UMETA(DisplayName = "Saboteur"),
	EMVPS_Reckless UMETA(DisplayName = "Reckless"),
	EMVPS_Saint UMETA(DisplayName = "Saint"),
	EMVPS_Thief UMETA(DisplayName = "Thief"),
	EMVPS_AttachmentIssues UMETA(DisplayName = "AttachmentIssues"),
	EMVPS_Max UMETA(DisplayName = "Max")
};

USTRUCT(BlueprintType)
struct FPlayerData
{
	GENERATED_BODY()

	FPlayerData()
	{
		bIsAssigned = false;
		Name = "Player";
		PlayerID = -1;
		CharacterChoice = 0;
		TotalScore = 0;
		CurrentRoundScore = 0;
		ScoredOnOtherGoal = 0;
		TimesBumpedOtherPlayers = 0;
		TimesCordBroke = 0;
		PatientsKilled = 0;
		HealthyPatientsRescued = 0;
		PreviousTotalScore = 0;
		PatientsStolen = 0;
		TimeHoldingPatients = 0;
	}
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bIsAssigned;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FString Name;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int PlayerID;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int CharacterChoice;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int TotalScore;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int CurrentRoundScore;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<int> RoundsScore;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int ScoredOnOtherGoal;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int TimesBumpedOtherPlayers;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int TimesCordBroke;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int PatientsKilled;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int HealthyPatientsRescued;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int PreviousTotalScore;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int PatientsStolen;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int TimeHoldingPatients;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<EMVPS> BonusMvps;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<EMVPS> DeductionMvps;
};

UCLASS()
class FG21FT_GP4_TEAM05_API UGP4_StatTrackingSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UGP4_StatTrackingSubsystem(){
		ConnectedPlayersAmount = 0;
	}

	static constexpr int Max_Player_Amount = 4;

	UPROPERTY()
	FPlayerData PlayerDataList[Max_Player_Amount];

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int ConnectedPlayersAmount;
	
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UFUNCTION(BlueprintCallable, Category = "PlayerInfo")
	void SetUpPlayersData(const int Id);
	
	UFUNCTION(BlueprintCallable, Category = "PlayerInfo")
	void SetPlayerChoice(const int PlayerId, const int CharacterChoice);
	
	UFUNCTION(BlueprintCallable, Category = "StatTracking")
	FPlayerData& GetPlayerData(const int PlayerId);
	
	UFUNCTION(BlueprintCallable, Category = "StatTracking")
	void UpdatePlayerRoundScore(const int PlayerId,int Score);
	
	UFUNCTION(BlueprintCallable, Category = "StatTracking")
	void AddAllPlayersRoundScoreToRound();
	
	UFUNCTION(BlueprintCallable, Category = "StatTracking")
	void ResetAllPlayersCurrentRoundScore();
	
	UFUNCTION(BlueprintCallable, Category = "StatTracking")
	void UpdatePlayersTotalScore();
	
	UFUNCTION(BlueprintCallable, Category = "StatTracking")
	void UpdateScoreInOtherPlayersGoal(const int PlayerId, const int GoalId);
	
	UFUNCTION(BlueprintCallable, Category = "StatTracking")
	void UpdateTimesBumpedOtherPlayers(const int PlayerId);
	
	UFUNCTION(BlueprintCallable, Category = "StatTracking")
	void UpdateTimesCordBroke(const int PlayerId);
	
	UFUNCTION(BlueprintCallable, Category = "StatTracking")
	int GetWinningPlayerId();
	
	UFUNCTION(BlueprintCallable, Category = "StatTracking")
	void UpdatePatientsKilled(const int PlayerId);
	
	UFUNCTION(BlueprintCallable, Category = "StatTracking")
	void UpdateHealthyPatientsRescued(const int PlayerId);
	
	UFUNCTION(BlueprintCallable, Category = "StatTracking")
	void ResetStatTracking();

	UFUNCTION(BlueprintCallable, Category = "StatTracking")
	void UpdatePatientsStolen(const int PlayerId);

	UFUNCTION(BlueprintCallable, Category = "StatTracking")
	void UpdateTimeHoldingPatient(const int PlayerId, int Time);

	UFUNCTION(BlueprintCallable, Category = "StatTracking")
	void SetMvps();

	UFUNCTION(BlueprintCallable, Category = "StatTracking")
	int GetMvpStat(const int PlayerId, EMVPS Mvp);

	UFUNCTION(BlueprintCallable, Category = "StatTracking")
	void UpdateTotalScoreMvps(const int PlayerId, const int Score);

	UFUNCTION()
	bool CheckIfIndexIsOutOfBounds(const int Index);
};
