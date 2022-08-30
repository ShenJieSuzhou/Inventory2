// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "MyTestWidget.generated.h"

/**
 * 
 */
UCLASS()
class DP_API UMyTestWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual bool Initialize() override;

	UFUNCTION()
	void OnUseItem();
	
public:
	UPROPERTY(Meta = (BindWidget))
	class UButton* UseButton;
};
