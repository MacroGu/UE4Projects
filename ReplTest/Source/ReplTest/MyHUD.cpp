// Fill out your copyright notice in the Description page of Project Settings.

#include "MyHUD.h"
#include "Engine/Canvas.h"
#include "ReplTestCharacter.h"
#include "UObject/ConstructorHelpers.h"


AMyHUD::AMyHUD()
{
	Font = NULL;

	if (GetNetMode() == NM_Client)
	{
		ConstructorHelpers::FObjectFinder<UFont> FontObject(TEXT("Font'/Game/TopDownCPP/Blueprints/NewFont.NewFont'"));
		if (FontObject.Object)
		{
			Font = FontObject.Object;
		}
	}
}

void AMyHUD::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AMyHUD::DrawHUD()
{
	DrawRoleAlias();
}

void AMyHUD::DrawRoleAlias()
{
	for (TObjectIterator<AReplTestCharacter> Itr; Itr; ++Itr)
	{
		AReplTestCharacter* ForActor = *Itr;
		FBox BB = ForActor->GetComponentsBoundingBox();
		FVector Center = ForActor->GetActorLocation();
		FVector2D Center2D = FVector2D(Canvas->Project(FVector(Center.X, Center.Y, Center.Z)));
		Center2D.Y -= 50;

		FString UserAlias = ForActor->Alias();
		FCanvasTextItem TextItem(Center2D, FText::FromString(UserAlias), Font, FColor::Red);
		Canvas->DrawItem(TextItem);
	}
}

