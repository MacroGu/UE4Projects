// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/BagWidget/ExBaseBag.h"
#include "ExBagBlock.h"

void UExBaseBag::UpdateBlock(uint8 BlockId)
{
	BlockGroup[BlockId]->UpdateBlock();
}
