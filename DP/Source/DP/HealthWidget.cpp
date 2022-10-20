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
	// ¿ªÆô¶¨Ê±Æ÷
	FTimerManager &timerManager = GetWorld()->GetTimerManager();
	timerManager.SetTimer(MemberTimerHandle, this, &UHealthWidget::Repeating, 2.0f, true, 5.0f);
}

void UHealthWidget::Repeating()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("11111111"));
	pValue += 5.0f;
	if(pValue > 100)
	{
		//timerManager.ClearTimer(MemberTimerHandle);
		return;
	}
	HealthProgressBar->SetPercent(pValue/100);
}