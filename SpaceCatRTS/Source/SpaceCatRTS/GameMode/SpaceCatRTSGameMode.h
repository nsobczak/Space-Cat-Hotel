#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SpaceCatRTSGameMode.generated.h"

UCLASS(minimalapi)
class ASpaceCatRTSGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASpaceCatRTSGameMode();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** AudioComponent currently playing*/
	UPROPERTY(BlueprintReadOnly, Category = "Audio_Settings")
		class UAudioComponent* CurrentTheme_AC;

	/** Main theme for the map*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio")
		class USoundBase* MapTheme;
};



