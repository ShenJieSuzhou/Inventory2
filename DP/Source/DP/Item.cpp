// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"

UItem::UItem()
{
	Weight = 1.f;
	ItemDisplayName = FText::FromName("Item");
	UseActionText = FText::FromString("Use");

}

//void UItem::OnUse(class ADPCharacter* Character)
//{
//	
//}