// Fill out your copyright notice in the Description page of Project Settings.

#include "FormatText.h"


UFormatText::~UFormatText()
{
}


UFormatText::UFormatText()
{
}

void UFormatText::Init()
{

}

void UFormatText::SetAlignment(FVector2D& position, int32* lineW, int32* textH,
	FTextFormatSettings* textSettings, FVector2D* TextureSize, int LinesAmount)
{
	LinesAmount += 1;

	switch (textSettings->horizontalAlignment)
	{
	case EHorizontalAlignment::HAlign_Center:
	{
		position.X = (TextureSize->X / 2) - (*lineW / 2);
		break;
	}
	case EHorizontalAlignment::HAlign_Right:
	{
		position.X = TextureSize->X - *lineW;
		break;
	}
	default:
		position.X = 0;
		break;
	}



	switch (textSettings->verticalAlignment)
	{
	case EVerticalAlignment::VAlign_Bottom:
	{
		position.Y = TextureSize->Y - (*textH * LinesAmount);
		break;
	}
	case EVerticalAlignment::VAlign_Center:
	{
		position.Y = (TextureSize->Y / 2) - ((*textH * LinesAmount) / 2);
		break;
	}
	default:
		position.Y = 0;
		break;
	}
}

void UFormatText::AddPadding(FMargin* padding, FVector2D& position)
{
	position.X += padding->Left - padding->Right;
	position.Y += padding->Top - padding->Bottom;
}

TArray<FWrappedStringElement> UFormatText::SplitTextIntoLines(FTextFormatSettings* textSettings,
	int32* textH, FVector2D& TextureSize)
{
	TArray<FWrappedStringElement> lines;

	if (textSettings->wrapTextAt == 0)
	{
		lines.Add(FWrappedStringElement(*textSettings->text, 0, 0));
		return lines;
	}


	FTextSizingParameters params;
	params.DrawFont = textSettings->font;
	params.DrawX = 0;
	params.DrawY = 0;
	params.DrawXL = textSettings->wrapTextAt;
	params.DrawYL = *textH;
	params.Scaling = FVector2D(textSettings->fontScale, textSettings->fontScale);
	FCanvasWordWrapper wrapper;

	UCanvas::WrapString(wrapper, params, 0, *textSettings->text, lines);

	return lines;
}


