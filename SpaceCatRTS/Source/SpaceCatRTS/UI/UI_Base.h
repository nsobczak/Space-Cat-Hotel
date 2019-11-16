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

};


