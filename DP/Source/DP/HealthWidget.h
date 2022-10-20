// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "HealthWidget.generated.h"

/**
 * 
 */
UCLASS()
class DP_API UHealthWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    virtual bool Initialize() override;

	UFUNCTION()
	void TestLoadEvent();

	void Repeating();


public:
	UPROPERTY(Meta = (BindWidget))
	UProgressBar *HealthProgressBar;
	UPROPERTY(Meta = (BindWidget))
	UButton *TestBtn;
	UPROPERTY(Meta = (BindWidget))
	UTextBlock *processValue;

	float pValue;

	FTimerHandle MemberTimerHandle;
	//const FTimerManager &timerManager;
};
