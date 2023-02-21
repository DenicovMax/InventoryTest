// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "MediaAssets/Public/MediaPlayer.h"
#include "ITMediaWidget.generated.h"

class UImage;
/**
 * 
 */
UCLASS()
class INVENTORYTEST_API UITMediaWidget : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

protected:

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* BrowseButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* Browse;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* CloseButton;
	
	UPROPERTY(EditDefaultsOnly, Category = MediaPlayer)
	UMediaPlayer* MediaPlayer;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UImage* MediaImage;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UImage* VideoImage;

public:

	void OnBrowseButtonPressed();

	void OnCloseButtonPressed();
};
