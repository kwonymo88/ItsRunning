// Fill out your copyright notice in the Description page of Project Settings.


#include "TzHorizontalBoxEx.h"

UTzHorizontalBoxEx::UTzHorizontalBoxEx(const FObjectInitializer & ObjectInitializer)
	: Super(ObjectInitializer)
{

}

UPanelSlot* UTzHorizontalBoxEx::CustomInsertChildAt(int32 Index, UWidget* Content)
{
	UPanelSlot* pNewPanelSlot = InsertChildAt(Index, Content);
	InvalidateLayoutAndVolatility();
	return pNewPanelSlot;
}

void UTzHorizontalBoxEx::CustomShiftChild(int32 Index, UWidget* Child)
{
	ShiftChild(Index, Child);
	InvalidateLayoutAndVolatility();
}
