// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemData.h"
#include "SlotWidget.h"
#include "Components/Button.h "
#include "Components/Image.h "
#include "Components/ScrollBox.h "
#include "Components/TextBlock.h "
#include "Blueprint/WidgetTree.h"
#include "Components/TextBlock.h"
#include "Components/PanelWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Runtime/UMG/Public/Components/UniformGridPanel.h"
#include "Runtime/UMG/Public/Components/UniformGridSlot.h"
#include "Runtime/UMG/Public/Components/VerticalBox.h"
#include "Blueprint/UserWidget.h"
#include "InventoryUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API UInventoryUserWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(EditAnyWhere, Category = JeTest)
	TSubclassOf<USlotWidget> SlotWidget;

public:
	// UWidget interface
	virtual TSharedRef<SWidget> RebuildWidget() override;

private:
	virtual void NativeConstruct() override;

private:
	void SetPositionWidgetInGridPanel(UUserWidget* TheWidget, int32 Column, int32 Row);

	USlotWidget* AddWidgetSlotInPanel(UPanelWidget* Parent);

	USlotWidget* AddWidgetSlotInGridPanel(UUniformGridPanel* Parent, int32 Column, int32 Row);

public:
	void InitParentCategory();

	TArray<FTableRowInventory> FilterInventoryCategory(const TArray<FTableRowInventory> &Items, const FString &Category);

	void ShowInventoryUniform(const TArray<FTableRowInventory> &Items, int32 Column, int32 Row = 1);

	void ShowInventoryUniformInverse(const TArray<FTableRowInventory> &Items, int32 Column, int32 Limit);

	template<typename T>
	void ShowInventoryInPanel(const TArray<FTableRowInventory> &Items, FName NameWidget)
	{
		T* TargetWidget = Cast<T>(GetWidgetFromName(NameWidget));

		if (!TargetWidget)
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, "TargetWidget est null");
			return;
		}

		if (!TargetWidget->GetClass()->IsChildOf<UPanelWidget>())
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, "Pas enfant de Panel");
			return;
		}

		USlotWidget* TempWidget;
		for (int32 i = 0; i < Items.Num(); i++)
		{
			TempWidget = AddWidgetSlotInPanel(TargetWidget);
			if (TempWidget)
			{
				//TempWidget->ItemTarget->SetInfosItem(Items[i]);
			}
		}
		AddToViewport();
	}

	void ReceiveInfos(USlotWidget* TheSlotWidget, const FTableRowInventory &Item, int32 Id);

	void RemoteInventory();

	UFUNCTION(BlueprintCallable, category = testItemBase)
	void SetOwnerInventory(AActor* NewOwner) { OwnerInventory = NewOwner; }

	UFUNCTION(BlueprintCallable, category = testItemBase)
	AActor* GetOwnerInventory() { return OwnerInventory; }

	UFUNCTION(BlueprintCallable, category=test)
	void SetSortCategory(const FString &NewSortCategory) { SortCategory = NewSortCategory; }

private:
	UPROPERTY(VisibleAnyWhere, Category=test )
	TMap<FString, FArrayString> ParentCategory;

	UPROPERTY(VisibleAnyWhere, Category = test)
	FString SortCategory = "Equipment";

	AActor* OwnerInventory = nullptr;
};
