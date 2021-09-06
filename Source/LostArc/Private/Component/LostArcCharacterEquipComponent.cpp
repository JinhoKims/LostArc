// Fill out your copyright notice in the Description page of Project Settings.

#include "Component/LostArcCharacterEquipComponent.h"
#include "Abilities/Items/LostArcItemBase.h"
#include "Abilities/Items/Equip/LostArcItemEquipBase.h"

// Sets default values for this component's properties
ULostArcCharacterEquipComponent::ULostArcCharacterEquipComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;

	for (int i = 0; i < 3; i++)
	{
		EquipSlot.Add((EAccessoryType)i);
		EquipMaxSlot.Add((EAccessoryType)i);
	}
}
void ULostArcCharacterEquipComponent::InitializeComponent()
{
	Super::InitializeComponent();
	
	for (int32 i = 0; i < 3; i++)
	{
		if (EquipMaxSlot.Find((EAccessoryType)i) != nullptr)
		{
			EquipSlot.Find((EAccessoryType)i)->EquipArray.SetNum(*EquipMaxSlot.Find((EAccessoryType)i));
		}
	}
}
void ULostArcCharacterEquipComponent::EndPlay(EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	EquipSlot.Empty();
}

void ULostArcCharacterEquipComponent::UseAbility(int32 SlotIndex)
{
	const EAccessoryType SlotType = IndexDecoding(SlotIndex);
	
	if(EquipSlot.Find(SlotType)->EquipArray[SlotIndex] != nullptr)
	{
		if(Cast<ALostArcCharacter>(GetOwner())->InventoryComponent->SetSlotData(EquipSlot.Find(SlotType)->EquipArray[SlotIndex]))
		{
			EquipSlot.Find(SlotType)->EquipArray[SlotIndex]->Dismount(Cast<ALostArcCharacter>(GetOwner()));
			EquipSlot.Find(SlotType)->EquipArray[SlotIndex] = nullptr;
			EquipSlotUpdate.Broadcast(IndexEncoding(SlotType, SlotIndex));
		}
	}
}

ULostArcAbilityBase* ULostArcCharacterEquipComponent::TransAbil(int32 SlotIndex)
{
	auto TransUnit = GetEquipItem(SlotIndex);

	if(TransUnit != nullptr)
	{
		TransUnit->Dismount(Cast<ALostArcCharacter>(GetOwner()));

		auto SlotType = IndexDecoding(SlotIndex);
		EquipSlot.Find(SlotType)->EquipArray[SlotIndex] = nullptr;
		EquipSlotUpdate.Broadcast(IndexEncoding(SlotType, SlotIndex));
		return TransUnit;
	}
	
	return nullptr;
}

void ULostArcCharacterEquipComponent::EquipMounts(ULostArcItemEquipBase* NewEquip) // 이미 능력치가 증가된 상태임!!
{
	if (NewEquip == nullptr) return;
	
	for (int32 i = 0; i < *EquipMaxSlot.Find(NewEquip->GetAcType()); i++) // EquipSlot has Empty
	{
		if(EquipSlot.Find(NewEquip->GetAcType())->EquipArray[i] == nullptr)
		{
			EquipSlot.Find(NewEquip->GetAcType())->EquipArray[i] = NewEquip;
			EquipSlotUpdate.Broadcast(IndexEncoding(NewEquip->GetAcType(), i));
			return;
		}
	}

	// EquipSlot has Fully
	Swap(EquipSlot.Find(NewEquip->GetAcType())->EquipArray[0], NewEquip);
	if(Cast<ALostArcCharacter>(GetOwner())->InventoryComponent->SetSlotData(NewEquip)) // 스왑 성공
	{
		NewEquip->Dismount(Cast<ALostArcCharacter>(GetOwner()));
		EquipSlotUpdate.Broadcast(IndexEncoding(NewEquip->GetAcType(), 0));
	}
	else // 스왑 실패
	{
		Swap(EquipSlot.Find(NewEquip->GetAcType())->EquipArray[0], NewEquip);
		NewEquip->Dismount(Cast<ALostArcCharacter>(GetOwner()));
	}
}
void ULostArcCharacterEquipComponent::SwappingSlot(int32 OwnerIndex, int32 DistIndex)
{
	auto OwnerType = IndexDecoding(OwnerIndex);
	auto DistType = IndexDecoding(DistIndex);
	
	if(EquipSlot.Find(OwnerType)->EquipArray[OwnerIndex] == nullptr || OwnerIndex == DistIndex || OwnerType != DistType ) return;
	
	if (EquipSlot.Find(DistType)->EquipArray[DistIndex] == nullptr)
	{
		EquipSlot.Find(DistType)->EquipArray[DistIndex] = EquipSlot.Find(OwnerType)->EquipArray[OwnerIndex];
		EquipSlot.Find(OwnerType)->EquipArray[OwnerIndex] = nullptr;
		UE_LOG(LogTemp,Warning,TEXT("Move Slot"));
	}
	else
	{
		Swap(EquipSlot.Find(OwnerType)->EquipArray[OwnerIndex],
			EquipSlot.Find(DistType)->EquipArray[DistIndex]);
		UE_LOG(LogTemp,Warning,TEXT("Swap Slot"));
	}

	EquipSlotUpdate.Broadcast(IndexEncoding(OwnerType,OwnerIndex));
	EquipSlotUpdate.Broadcast(IndexEncoding(DistType,DistIndex));
}
void ULostArcCharacterEquipComponent::SwappingSlot(UActorComponent* OwnerComponent, int32 OwnerIndex, int32 DistIndex)
{
	auto InvenComponent = Cast<ULostArcInventoryComponent>(OwnerComponent);
	if(InvenComponent == nullptr || Cast<ULostArcItemEquipBase>(InvenComponent->GetSlotData(OwnerIndex)) == nullptr) return;
	
	if(GetEquipItem(DistIndex) == nullptr) // 마침 장비 슬롯이 null 일 때
	{
		if(GetIndexACType(DistIndex) != Cast<ULostArcItemEquipBase>(InvenComponent->GetSlotData(OwnerIndex))->GetAcType()) return;
		SetEqiupItem(Cast<ULostArcItemEquipBase>(InvenComponent->TransAbil(OwnerIndex)), DistIndex);
	}
	else // Swap
	{
		if(GetEquipItem(DistIndex)->GetAcType() == Cast<ULostArcItemEquipBase>(InvenComponent->GetSlotData(OwnerIndex))->GetAcType()) // 같은 장비류인 경우
		{ 
			auto NewData = Cast<ULostArcItemEquipBase>(InvenComponent->TransAbil(OwnerIndex));
			if(InvenComponent->SetSlotData(GetEquipItem(DistIndex), OwnerIndex))
			{
				GetEquipItem(DistIndex)->Dismount(Cast<ALostArcCharacter>(GetOwner()));
				SetEqiupItem(NewData, DistIndex);
			}
		}
	}
}

int32 ULostArcCharacterEquipComponent::IndexEncoding(EAccessoryType AcType, int32 Index) 
{
	switch (AcType)
	{
	case EAccessoryType::Necklace:
		return Index;
	case EAccessoryType::Earring:
		return Index+=1;
	case EAccessoryType::Ring:
		return Index+=3;
	}
	
	return -1;
}
EAccessoryType ULostArcCharacterEquipComponent::IndexDecoding(int32& SlotIndex)
{
	switch (SlotIndex)
	{
	case 0:
		return EAccessoryType::Necklace;
	case 1:
	case 2:
		SlotIndex-=1;
		return EAccessoryType::Earring;
	case 3:
	case 4:
		SlotIndex-=3;
		return EAccessoryType::Ring;
	}
	
	return EAccessoryType::Necklace;
}

EAccessoryType ULostArcCharacterEquipComponent::GetIndexACType(int32 Index)
{
	switch (Index)
	{
	case 0:
		return EAccessoryType::Necklace;
	case 1:
	case 2:
		return EAccessoryType::Earring;
	case 3:
	case 4:
	return EAccessoryType::Ring;
	}
	return EAccessoryType::Necklace;
} // 인덱스 타입 재설계 요망
ULostArcItemEquipBase* ULostArcCharacterEquipComponent::GetEquipItem(int32 Index)
{
	return EquipSlot.Find(IndexDecoding(Index))->EquipArray[Index];
}
bool ULostArcCharacterEquipComponent::SetEqiupItem(ULostArcItemBase* OwnerItem, int32 DistIndex)
{
	auto DistType = IndexDecoding(DistIndex);

	if(Cast<ULostArcItemEquipBase>(OwnerItem) != nullptr && DistType == Cast<ULostArcItemEquipBase>(OwnerItem)->GetAcType())
	{
		EquipSlot.Find(DistType)->EquipArray[DistIndex] = Cast<ULostArcItemEquipBase>(OwnerItem); // Get()으로 하면 R-Value가 불러와서(주소를 저장하려면 반드시 포인터가 필요) 안된다.
		EquipSlot.Find(DistType)->EquipArray[DistIndex]->Equipment(Cast<ALostArcCharacter>(GetOwner()));
		EquipSlotUpdate.Broadcast(IndexEncoding(DistType, DistIndex));
		return true;
	}
	
	return false;
}