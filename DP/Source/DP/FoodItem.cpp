// Fill out your copyright notice in the Description page of Project Settings.


#include "FoodItem.h"
#include "DPCharacter.h"

void UFoodItem::Use(class ADPCharacter* Character)
{
	if(Character)
	{
		Character->Health += HealthToHeal;
	}
}