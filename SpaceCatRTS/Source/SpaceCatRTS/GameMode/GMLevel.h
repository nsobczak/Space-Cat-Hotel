#pragma once

#include "CoreMinimal.h"
#include "GameMode/SpaceCatRTSGameMode.h"
#include "GMLevel.generated.h"

/**
 *
 */
UCLASS()
class SPACECATRTS_API AGMLevel : public ASpaceCatRTSGameMode
{
	GENERATED_BODY()

public:
	AGMLevel();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "GameLogic", Meta = (BlueprintProtected = "true"))
		virtual void SetupGame();

	UFUNCTION(BlueprintPure, Category = "GameTimer")
		FORCEINLINE float GetCurrentGameTimer() { return GameTimer; }
	UFUNCTION(BlueprintPure, Category = "GameTimer")
		FORCEINLINE int32 GetCurrentGameTimerMinutes() { return (int32)GameTimer / 60; }
	UFUNCTION(BlueprintPure, Category = "GameTimer")
		FORCEINLINE int32 GetCurrentGameTimerSeconds() { return (int32)GameTimer % 60; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	class ALevelSettings* LevelSettings;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Timer")
		float GameTimer;

	virtual void GameOver();

	virtual void HandleGoals();
};
