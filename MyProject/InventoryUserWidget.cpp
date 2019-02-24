// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryUserWidget.h"
#include "Engine.h"

void UInventoryUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

TSharedRef<SWidget> UInventoryUserWidget::RebuildWidget()
{
	TSharedRef<SWidget> OurWidget = Super::RebuildWidget();

	return OurWidget;
}

void UInventoryUserWidget::InitParentCategory()
{
	if (ParentCategory.Num() == 0)
	{
		FArrayString tableEquipment;

		tableEquipment.FoString = {
			"Hat",
			"Shoulder",
			"Mantle",
			"Backpack",
			"Amulet",
			"Ring",
			"Belt",
			"Boots",
		};

		ParentCategory.Add("Equipment", tableEquipment);

		FArrayString tableConsommable;

		tableConsommable.FoString = {
			"Potion",
			"Bread"
		};

		ParentCategory.Add("Consommable", tableConsommable);
	}
}

void UInventoryUserWidget::SetPositionWidgetInGridPanel(UUserWidget* TheWidget, int32 Column, int32 Row)
{
	if (UUniformGridSlot* slot = Cast<UUniformGridSlot>(TheWidget->Slot))
	{
		slot->SetColumn(Column);
		slot->SetRow(Row);
	}
}

USlotWidget* UInventoryUserWidget::AddWidgetSlotInPanel(UPanelWidget* Parent)
{
	USlotWidget* TargetWidget = CreateWidget<USlotWidget>(UGameplayStatics::GetPlayerController(GetWorld(), 0), SlotWidget);

	if (TargetWidget)
	{
		Parent->AddChild(TargetWidget);
		return TargetWidget;
	}

	return nullptr;
}

USlotWidget* UInventoryUserWidget::AddWidgetSlotInGridPanel(UUniformGridPanel* Parent, int32 Column, int32 Row)
{
	USlotWidget* TargetWidget = CreateWidget<USlotWidget>(UGameplayStatics::GetPlayerController(GetWorld(), 0), SlotWidget);

	if (TargetWidget)
	{
		Parent->AddChild(TargetWidget);

		if (UUniformGridSlot* slot = Cast<UUniformGridSlot>(TargetWidget->Slot))
		{
			slot->SetColumn(Column);
			slot->SetRow(Row);
		}

		return TargetWidget;
	}

	return nullptr;
}

void UInventoryUserWidget::ShowInventoryUniform(const TArray<FTableRowInventory> &Items, int32 Column, int32 Row)
{
	if (UUniformGridPanel* UniformGridPanel = Cast<UUniformGridPanel>(GetWidgetFromName("Inventory_Uniform")))
	{
		UniformGridPanel->ClearChildren();

		int32 Count = 0, BankNum = Items.Num();
		for (int32 CurrentRow = 0; CurrentRow < Row; CurrentRow++)
		{
			for (int32 CurrentColumn = 0; CurrentColumn < Column; CurrentColumn++)
			{
				if (USlotWidget* TempSlotWidget = AddWidgetSlotInPanel(UniformGridPanel))
				{
					SetPositionWidgetInGridPanel(TempSlotWidget, CurrentColumn, CurrentRow);

					if (Count < BankNum) {
						ReceiveInfos(TempSlotWidget, Items[Count], Count);
					}
				}

				Count++;
			}
		}
	}
}

void UInventoryUserWidget::ShowInventoryUniformInverse(const TArray<FTableRowInventory> &Items, int32 Column, int32 Limit)
{
	InitParentCategory();

	TArray<FTableRowInventory> NewItems;
	NewItems = FilterInventoryCategory(Items, SortCategory);

	int32 SizeInventory = NewItems.Num();

	UUniformGridPanel* UniformGridPanel = Cast<UUniformGridPanel>(GetWidgetFromName("Inventory_Uniform"));

	if (!UniformGridPanel)
	{
		return;
	}

	UniformGridPanel->ClearChildren();

	int32 Count = 0, CurrentRow = FMath::RoundFromZero((float)Limit / Column) - 1.0f;

	while (Count < Limit)
	{
		for (int32 CurrentColumn = Column - 1; CurrentColumn >= 0; CurrentColumn--)
		{
			if (Count < Limit)
			{
				if (USlotWidget* TempSlotWidget = AddWidgetSlotInGridPanel(UniformGridPanel, CurrentColumn, CurrentRow))
				{
					if (Count < SizeInventory)
					{
						ReceiveInfos(TempSlotWidget, NewItems[Count], Count);
					}
				}
			}

			Count++;
		}

		CurrentRow--;
	}
}

void UInventoryUserWidget::ReceiveInfos(USlotWidget* TheSlotWidget, const FTableRowInventory &Item, int32 Id)
{
	if (UItemBaseWidget* ItemBaseWidget = Cast<UItemBaseWidget>(GetWidgetFromName("Widget_Description")))
	{
		TheSlotWidget->SetItemDescription(ItemBaseWidget);
	}

	TheSlotWidget->SetId(Id);
	TheSlotWidget->SetItemInfos(Item);
	TheSlotWidget->SetParentInventory(this);
}

void UInventoryUserWidget::RemoteInventory()
{
	if (UScrollBox* ScrollBox = Cast<UScrollBox>(GetWidgetFromName("Inventory_Vertical")))
	{
		ScrollBox->ClearChildren();
	}

	if (UUniformGridPanel* UniformGridPanel = Cast<UUniformGridPanel>(GetWidgetFromName("Inventory_Uniform")))
	{
		UniformGridPanel->ClearChildren();
	}

	RemoveFromParent();
}

TArray<FTableRowInventory> UInventoryUserWidget::FilterInventoryCategory(const TArray<FTableRowInventory> &Items, const FString &Category)
{
	TArray<FTableRowInventory> NewItems;

	if (!ParentCategory.Contains(Category))
	{
		return NewItems;
	}

	const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("ItemCategory"), true);

	for (int32 i = 0; i < Items.Num(); i++)
	{
		FString theKey = EnumPtr->GetNameStringByValue(Items[i].ItemData.category.GetValue());

		if (ParentCategory[Category].FoString.Contains(theKey))
		{
			NewItems.Add(Items[i]);
		}
	}

	return NewItems;
}
