// Fill out your copyright notice in the Description page of Project Settings.


#include "MyItemWidget.h"

void UMyItemWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// ÉèÖÃ UI
	if (nullptr != Thumbnail)
	{
		Thumbnail->SetBrushFromTexture(Item->Thumbnail, true);
	}

	if (nullptr != ItemName)
	{
		ItemName->SetText(Item->ItemDisplayName);
	}
}

bool UMyItemWidget::Initialize()
{
	if(!Super::Initialize())
	{
		return false;
	}

	if (nullptr != UseButton)
	{
		UseButton->OnClicked.__Internal_AddDynamic(this, &UMyItemWidget::OnUseItem, FName("OnUseItem"));
	}

	return true;
}

void UMyItemWidget::OnUseItem()
{
	UE_LOG(LogTemp, Warning, TEXT("btn clicked"));
}
