#pragma once

#include "CoreMinimal.h"
#include "GameFramework/WorldSettings.h"
#include "Utils/Struct/StructLevelInfo.h"
#include "LevelSettings.generated.h"

/**
 *
 */
UCLASS()
class SPACECATRTS_API ALevelSettings : public AWorldSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Level info")
		FStructLevelInfo LevelInfo;
};
