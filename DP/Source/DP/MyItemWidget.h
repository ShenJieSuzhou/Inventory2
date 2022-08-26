// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "MyItemWidget.generated.h"

/**
 * 
 */
UCLASS()
class DP_API UMyItemWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(Meta = (BindWidget))
	UButton* UseButton;

	UPROPERTY(Meta = (BindWidget))
	UImage* Thumbnail;

	UPROPERTY(Meta = (BindWidget))
	UTextBlock* ItemName;

};
