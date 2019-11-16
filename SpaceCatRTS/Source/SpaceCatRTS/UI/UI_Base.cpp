#include "UI_Base.h"
#include "UMG/Public/UMG.h"


UUI_Base::UUI_Base(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}


void UUI_Base::BuildWidget()
{
	// Set Up Root Widget
	UCanvasPanel* RootWidget = Cast<UCanvasPanel>(GetRootWidget());
	if (!RootWidget)
		UE_LOG(LogTemp, Error, TEXT("RootWidget is null"));

	//add elements here
}

void UUI_Base::NativeConstruct()
{
	// Do some custom setup
	BuildWidget();

	// Call the Blueprint "Event Construct" node
	Super::NativeConstruct();
}


void UUI_Base::ShowInfo()
{
	this->SetVisibility(ESlateVisibility::Visible);
}

void UUI_Base::HideInfo()
{
	this->SetVisibility(ESlateVisibility::Hidden);
}

//void UUI_Base::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
//{
//
//}