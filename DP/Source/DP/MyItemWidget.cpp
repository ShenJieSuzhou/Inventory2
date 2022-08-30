// Fill out your copyright notice in the Description page of Project Settings.


#include "MyItemWidget.h"

void UMyItemWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//// ÉèÖÃ UI 
	Thumbnail->SetBrushFromTexture(Item->Thumbnail, true);
	ItemName->SetText(Item->ItemDisplayName);

	UseButton->OnClicked.AddDynamic(this, &UMyItemWidget::OnUseItem);
	UE_LOG(LogTemp, Warning, TEXT("NativeConstruct"));
}

void UMyItemWidget::OnUseItem()
{
	UE_LOG(LogTemp, Warning, TEXT("btn clicked"));
}
