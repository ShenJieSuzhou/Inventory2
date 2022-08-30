// Fill out your copyright notice in the Description page of Project Settings.


#include "MyTestWidget.h"

bool UMyTestWidget::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}

	if (nullptr != UseButton)
	{
		UseButton->OnClicked.__Internal_AddDynamic(this, &UMyTestWidget::OnUseItem, FName("OnUseItem"));
	}

	//// ÉèÖÃ UI
	//if(nullptr != Thumbnail)
	//{
	//	Thumbnail->SetBrushFromTexture(Item->Thumbnail, true);
	//}

	//if(nullptr != ItemName)
	//{
	//	ItemName->SetText(Item->ItemDisplayName);
	//}
	
	return true;
}

void UMyTestWidget::OnUseItem()
{
	UE_LOG(LogTemp, Warning, TEXT("btn clicked"));
}