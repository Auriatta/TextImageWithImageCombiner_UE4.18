// Fill out your copyright notice in the Description page of Project Settings.

#include "TextureTextComponent.h"


// Sets default values
UTextureTextComponent::UTextureTextComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	FormatText_ = CreateDefaultSubobject<UFormatText>("FormatText_");
	

}

void UTextureTextComponent::CombineTextWithTexture(FTextFormatSettings textFormatSettings,
	UTexture* Texture, UCanvasRenderTarget2D*& OutTexture, FVector2D TextureSize)
{
	TextureTextMarge_ = NewObject<UTextureTextMarge>();

	TextureTextMarge_->Init(TextureSize);
	TextureTextMarge_->InsertBaseTexture(Texture);
	

	int32 textH = textFormatSettings.font->GetStringHeightSize(*textFormatSettings.text);
	int32 lineW = 0;
	FVector2D linePosition = {};

	TextureTextMarge_->UpdateResource(); // Create canvas for FormatText
	FormatText_->Init();
	auto formatedLines = FormatText_->SplitTextIntoLines(
		&textFormatSettings, &textH, TextureSize);

	int multiply = 1;
	for (auto line : formatedLines)
	{
		textFormatSettings.font->GetStringHeightAndWidth(line.Value,
			textH, lineW);

		FormatText_->SetAlignment(linePosition, &lineW, &textH,
			&textFormatSettings, &TextureSize, formatedLines.Num());
		FormatText_->AddPadding(&textFormatSettings.padding,
			linePosition);

		linePosition.Y += (float)(multiply * textH);

		TextureTextMarge_->InsertText(line, linePosition, &textFormatSettings);

		multiply++;
	}

	TextureTextMarge_->UpdateResource();
	OutTexture = TextureTextMarge_;
}

void UTextureTextComponent::CreateTextFormatSettingsData(
	FTextFormatSettings& textFormatSettings, FString text,
	UFont* font, FFontRenderInfo fontRenderInfo,
	FVector2D position, FLinearColor color, FMargin padding,
	EHorizontalAlignment horizontalAlignment,
	EVerticalAlignment verticalAlignment, float LegacyFontSize,
	float wrapTextAt)
{
	textFormatSettings.font = font;
	textFormatSettings.color = color.ToFColor(false);
	textFormatSettings.font->LegacyFontSize = LegacyFontSize;
	textFormatSettings.fontRenderInfo = fontRenderInfo;
	textFormatSettings.horizontalAlignment = horizontalAlignment;
	textFormatSettings.padding = padding;
	textFormatSettings.position = position;
	textFormatSettings.text = text;
	textFormatSettings.verticalAlignment = verticalAlignment;
	textFormatSettings.wrapTextAt = wrapTextAt;
}



