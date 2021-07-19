// Fill out your copyright notice in the Description page of Project Settings.


#pragma once

#include "CoreMinimal.h"
#include "Engine/Canvas.h"
#include "FormatText.h"
#include "Engine/CanvasRenderTarget2D.h"
#include "TextureTextMarge.generated.h"

/**
*
*/
USTRUCT()
struct FTextParam
{
	GENERATED_BODY()
		FWrappedStringElement TextElement;
	FVector2D position;
	FTextFormatSettings* textFormat;
};


UCLASS()
class UTextureTextMarge : public UCanvasRenderTarget2D
{
	GENERATED_BODY()
public:
	UTextureTextMarge();

	void InsertText(FWrappedStringElement TextElement,
		FVector2D position, FTextFormatSettings* textFormat);
	void InsertBaseTexture(UTexture* texture);
	void Init(FVector2D &textureSize);

protected:
	UTexture* Texture;

	UPROPERTY()
		TArray<FTextParam> TextParams;

	UFUNCTION()
		void UpdateResources(UCanvas* Canvas, int32 Width, int32 Height);


};