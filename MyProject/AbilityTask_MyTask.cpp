// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilityTask_MyTask.h"

UAbilityTask_MyTask* UAbilityTask_MyTask::CreateMyTask(UGameplayAbility * OwningAbility, FName TaskInstanceName, float examplevariable)
{

	UAbilityTask_MyTask* MyObj = NewAbilityTask<UAbilityTask_MyTask>(OwningAbility, TaskInstanceName);

	return MyObj;
}

void UAbilityTask_MyTask::PerformAction() const
{
	OnCalled.Broadcast(500.f, 42);
}

void UAbilityTask_MyTask::Activate()
{
	PerformAction();
}