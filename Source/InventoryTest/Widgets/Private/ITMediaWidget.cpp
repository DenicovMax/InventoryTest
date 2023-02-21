// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryTest/Widgets/Public/ITMediaWidget.h"
#include "DesktopPlatformModule.h"
#include "FileMediaSource.h"
#include "IDesktopPlatform.h"
#include "MediaSoundComponent.h"
#include "Components/Image.h"
#include "InventoryTest/Character/Public/ITCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetRenderingLibrary.h"

void UITMediaWidget::NativeConstruct()
{
	Super::NativeConstruct();

	/*if(BrowseButton)
	{
		BrowseButton->OnPressed.AddDynamic(this, &UITMediaWidget::OnBrowseButtonPressed);
	}

	if(CloseButton)
	{
		CloseButton->OnPressed.AddDynamic(this, &UITMediaWidget::OnCloseButtonPressed);
	}*/
}

void UITMediaWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	if(BrowseButton->IsPressed() == true)
	{
		OnBrowseButtonPressed();
	}
	if(CloseButton->IsPressed() == true)
	{
		OnCloseButtonPressed();
	}

	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UITMediaWidget::OnBrowseButtonPressed()
{
	if(MediaPlayer)
	{
		FString Path;

		IDesktopPlatform* Desktop = FDesktopPlatformModule::Get();

		if(Desktop)
		{
			auto* ParentHandle = FSlateApplication::Get().FindBestParentWindowHandleForDialogs(nullptr);

			const FString FileTypes = "All Files (*.PNG, *.JPEG, *.JPG, *.MP4)|*.PNG, *.JPEG, *.JPG, *.MP4|"
									"Video Files (*.MP4)|*.MP4|"
									"JPG Files (*.JPG)|*.JPG|"
									"PNG Files (*.PNG)|*.PNG|";

			TArray<FString> OutFiles;

			Desktop->OpenFileDialog(ParentHandle, "Choose Media", "", "",
																	FileTypes, 1, OutFiles);

			if(OutFiles.Num() > 0)
			{
				Path = OutFiles[0];
			}
		}

		UTexture2D* Tex = UKismetRenderingLibrary::ImportFileAsTexture2D(this, Path);
		//UMediaTexture* MediaTex = 

		UFileMediaSource* MediaSource =	NewObject<UFileMediaSource>();
		if(MediaSource)
		{
			MediaSource->FilePath = Path;
			MediaPlayer->OpenSource(MediaSource);
			
			VideoImage->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
			MediaPlayer->Play();
			//MediaImage->SetBrushFromTexture();

			/*UMediaSoundComponent* Sound = NewObject<UMediaSoundComponent>(MediaSource);
			if(Sound)
			{
				Sound->SetMediaPlayer(MediaPlayer);
				Sound->Activate();
			}*/
		}
		
		if(Tex)
		{
			MediaImage->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
			MediaImage->SetBrushFromTexture(Tex);
			MediaImage->Brush.ImageSize.X = Tex->GetSizeX();
			MediaImage->Brush.ImageSize.Y = Tex->GetSizeY();
		}
	}
	
}

void UITMediaWidget::OnCloseButtonPressed()
{
	if(AITCharacter* Character = Cast<AITCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
	{
		Character->HideMediaWidget();
		MediaPlayer->Close();
	}
}


