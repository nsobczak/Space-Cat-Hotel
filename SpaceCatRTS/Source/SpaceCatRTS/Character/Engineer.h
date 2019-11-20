#pragma once

#include "CoreMinimal.h"
#include "Character/Worker.h"
#include "Engineer.generated.h"

/**
 *
 */
UCLASS()
class SPACECATRTS_API AEngineer : public AWorker
{
	GENERATED_BODY()

public:
	AEngineer();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	virtual void DoNothing() override;

	UFUNCTION(BlueprintPure, Category = "Engineer")
		FORCEINLINE class AHotel* GetTargetHotel() { return TargetHotel; };

	UFUNCTION(BlueprintCallable, Category = "Engineer")
		bool AssignHotelToWork(class AHotel* newHotel);

	UFUNCTION(BlueprintCallable, Category = "Engineer")
		class AMine*  BuildMine(FVector location, EMineNature mineNature);
	UFUNCTION(BlueprintCallable, Category = "Engineer")
		class AHotel*  BuildHotel_PurpleCone(FVector location);// { return BuildHotel(location, EHotelNature::FHN_PURPLE_CONE); }
	UFUNCTION(BlueprintCallable, Category = "Engineer")
		class AHotel*  BuildHotel_YellowCube(FVector location);// { return BuildHotel(location, EHotelNature::FHN_YELLOW_CUBE); }
	UFUNCTION(BlueprintCallable, Category = "Engineer")
		class AHotel*  BuildHotel_RedCylinder(FVector location);// { return BuildHotel(location, EHotelNature::FHN_RED_CYLINDER); }

	UFUNCTION(BlueprintCallable, Category = "Engineer")
		void  ResetBuildPossibilities();

	UFUNCTION(BlueprintPure, Category = "Engineer")
		FORCEINLINE bool GetCanBuildMine() { return bCanBuildMine; };
	UFUNCTION(BlueprintPure, Category = "Engineer")
		FORCEINLINE bool GetCanBuildPurpleCone() { return bCanBuildPurpleCone; };
	UFUNCTION(BlueprintPure, Category = "Engineer")
		FORCEINLINE bool GetCanBuildYellowCube() { return bCanBuildYellowCube; };
	UFUNCTION(BlueprintPure, Category = "Engineer")
		FORCEINLINE bool GetCanBuildRedCylinder() { return bCanBuildRedCylinder; };

	UFUNCTION(BlueprintCallable, Category = "Engineer")
		void EnableCanBuildMine() { ResetBuildPossibilities(); bCanBuildMine = true; }
	UFUNCTION(BlueprintCallable, Category = "Engineer")
		void EnableCanBuildPurpleConeHotel() { ResetBuildPossibilities(); bCanBuildPurpleCone = true; };
	UFUNCTION(BlueprintCallable, Category = "Engineer")
		void EnableCanBuildYellowCubeHotel() { ResetBuildPossibilities(); bCanBuildYellowCube = true; };
	UFUNCTION(BlueprintCallable, Category = "Engineer")
		void EnableCanBuildRedCylinderHotel() { ResetBuildPossibilities(); bCanBuildRedCylinder = true; };

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mine")
		TSubclassOf<class AMine> BPOxygenMineToBuild;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mine")
		TSubclassOf<class AMine> BPRawMineToBuild;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hotel")
		TSubclassOf <class AHotel> BPPurpleConeHotelToBuild;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hotel")
		TSubclassOf <class AHotel> BPYellowCubeHotelToBuild;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hotel")
		TSubclassOf <class AHotel> BPRedCylinderHotelToBuild;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Debug")
		class AHotel* TargetHotel;

	void WorkAtHotel();

	class AHotel* BuildHotel(TSubclassOf <class AHotel> hotelBP, FVector location, EHotelNature hotelNature);

	bool bCanBuildMine, bCanBuildPurpleCone, bCanBuildYellowCube, bCanBuildRedCylinder;
};
