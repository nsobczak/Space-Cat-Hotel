#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI_Base.generated.h"

/**
 *
 */
UCLASS()
class SPACECATRTS_API UUI_Base : public UUserWidget
{
	GENERATED_BODY()

public:
	UUI_Base(const FObjectInitializer& ObjectInitializer);

	// Optionally override the Blueprint "Event Construct" event
	virtual void NativeConstruct() override;

	//// Optionally override the tick event
	//virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void BuildWidget();

	UFUNCTION(BlueprintCallable, Category = "UI_Base", Meta = (BlueprintProtected = "true"))
		void ShowInfo();
	UFUNCTION(BlueprintCallable, Category = "UI_Base", Meta = (BlueprintProtected = "true"))
		void HideInfo();


protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI_Base")
		FColor ButtonColor_Normal = FColor::FColor::FromHex("#000055FF");
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI_Base")
		FColor ButtonColor_Hover = FColor::FColor::FromHex("#4BA698FF");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI_Base")
		FColor ButtonColor_Pressed = FColor::FColor::FromHex("#00A68DFF");

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "UI_Base")
		FButtonStyle ButtonStyle;
};


