// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/FourTaleUserWidget.h"

void UFourTaleUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();
}
