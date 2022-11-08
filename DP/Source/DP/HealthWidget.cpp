// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthWidget.h"
#include "TimerManager.h"

bool UHealthWidget::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}

	if(TestBtn != nullptr)
	{
		TestBtn->OnClicked.__Internal_AddDynamic(this, &UHealthWidget::TestLoadEvent, FName("TestLoadEvent"));
	}

	return true;
}


void UHealthWidget::TestLoadEvent()
{
	FTimerManager& timerManager = GetWorld()->GetTimerManager();
	timerManager.SetTimer(MemberTimerHandle, this, &UHealthWidget::Repeating, 2.0f, true, 0);
}

void UHealthWidget::Repeating()
{
	pValue += 2.0f;
	if(pValue > 100)
	{
		GetWorld()->GetTimerManager().ClearTimer(MemberTimerHandle);
		return;
	}
	HealthProgressBar->SetPercent(pValue/100);
}