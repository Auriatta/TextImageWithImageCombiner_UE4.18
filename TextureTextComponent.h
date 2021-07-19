// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TextureTextMarge.h"
#include "Components/ActorComponent.h"
#include "TextureTextComponent.generated.h"


UCLASS(ClassGroup = (TextureText), meta = (BlueprintSpawnableComponent))
class TEXTURETEXT_API UTextureTextComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UTextureTextComponent();

	UFUNCTION(BlueprintCallable, Category = "TextureText")
		void CombineTextWithTexture(FTextFormatSettings textFormatSettings,
			UTexture* Texture, UCanvasRenderTarget2D*& OutTexture,
			FVector2D textureSize);

	UFUNCTION(BlueprintCallable, Category = "TextureText")
		void CreateTextFormatSettingsData(
			FTextFormatSettings& textFormatSettings,
			FString text,
			UFont* font,
			FFontRenderInfo fontRenderInfo,
			FVector2D position,
			FLinearColor color,
			FMargin padding,
			EHorizontalAlignment horizontalAlignment = EHorizontalAlignment::HAlign_Left,
			EVerticalAlignment verticalAlignment = EVerticalAlignment::VAlign_Top,
			float LegacyFontSize = 12,
			float wrapTextAt = 0);
protected:

	UPROPERTY()
		UTextureTextMarge* TextureTextMarge_;
	UPROPERTY()
		UFormatText* FormatText_;


	
};
