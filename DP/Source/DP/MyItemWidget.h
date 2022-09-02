// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Item.h"
#include "MyItemWidget.generated.h"

/**
 * 
 */
UCLASS()
class DP_API UMyItemWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	virtual bool Initialize() override;

	UFUNCTION()
	void OnUseItem();

public:
	UPROPERTY(Meta=(BindWidget))
	class UButton* UseButton;

	UPROPERTY(Meta=(BindWidget))
	class UImage* Thumbnail;

	UPROPERTY(Meta=(BindWidget))
	class UTextBlock* ItemName; 
	
	UPROPERTY()
	AActor* ItemClass;

	UPROPERTY()
	Integer CurrentStack;

	UPROPERTY()
	Integer MaxStack;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Item", Meta = (ExposeOnSpawn = true, InstanceEditable = true))
	UItem *Item;
};
