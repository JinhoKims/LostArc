// Fill out your copyright notice in the Description page of Project Settings.

#include "Component/LostArcCharacterEquipComponent.h"

#include "../../../../Plugins/Developer/RiderLink/Source/RD/thirdparty/spdlog/include/spdlog/fmt/bundled/format.h"
#include "Abilities/Items/LostArcItemBase.h"
#include "Abilities/Items/Equip/LostArcItemEquipBase.h"

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
	auto Equip = Cast<ULostArcItemEquipBase>(GetAbility(SlotIndex));
	if(Equip)
	{
		if(Cast<ALostArcCharacter>(GetOwner())->InventoryComponent->SetAbility(Equip))
		{
			Equip->Dismount(Cast<ALostArcCharacter>(GetOwner()));
			EquipSlot.Find(IndexDecoding(SlotIndex))->EquipArray[SlotIndex] = nullptr;
			EquipSlotUpdate.Broadcast(IndexEncoding(Equip->GetAcType(), SlotIndex));
		}
	}
}
void ULostArcCharacterEquipComponent::SwappingSlot(int32 OwnerIndex, int32 DistIndex, UActorComponent* OwnerComponent)
{
	if(OwnerComponent == nullptr) // 내부 슬롯 스왑
	{
		if(GetAbility(OwnerIndex) == nullptr || OwnerIndex == DistIndex) return;
		
		if (GetAbility(DistIndex) == nullptr) // 이동
		{
			auto OwnerEquip = Cast<ULostArcItemEquipBase>(GetAbility(OwnerIndex));
			if(OwnerEquip->GetAcType() != IndexDecoding(DistIndex, false)) return;
			SetAbility(GetAbility(OwnerIndex,true), DistIndex);
			UE_LOG(LogTemp,Warning,TEXT("Move Slot"));
		}
		else // 교체
		{
			auto OwnerEquip = Cast<ULostArcItemEquipBase>(GetAbility(OwnerIndex)), DistEquip = Cast<ULostArcItemEquipBase>(GetAbility(DistIndex));
			if(OwnerEquip->GetAcType() != DistEquip->GetAcType()) return;
			
			Swap(EquipSlot.Find(IndexDecoding(OwnerIndex))->EquipArray[OwnerIndex], EquipSlot.Find(IndexDecoding(DistIndex))->EquipArray[DistIndex]);
			UE_LOG(LogTemp,Warning,TEXT("Swap Slot"));

			EquipSlotUpdate.Broadcast(IndexEncoding(OwnerEquip->GetAcType(), OwnerIndex));
			EquipSlotUpdate.Broadcast(IndexEncoding(DistEquip->GetAcType(), DistIndex));
		}
	}
	else // 외부 슬롯 스왑
	{
		ILostArcCharacterInterface* Interface = Cast<ILostArcCharacterInterface>(OwnerComponent);
		if(Interface == nullptr) return;
		
		auto OwnerEquip = Cast<ULostArcItemEquipBase>(Interface->GetAbility(OwnerIndex));
		if(OwnerEquip == nullptr) return;
		
		if(GetAbility(DistIndex) == nullptr) // 이동
		{
			if(OwnerEquip->GetAcType() == IndexDecoding(DistIndex))
			{
				SetAbility(Interface->GetAbility(OwnerIndex, true), IndexEncoding(OwnerEquip->GetAcType(), DistIndex));
			}
		}
		else // 교체
		{
			if(Cast<ULostArcItemEquipBase>(GetAbility(DistIndex))->GetAcType() == OwnerEquip->GetAcType()) // 같은 장비류인 경우
			{
				auto OwnerData = Interface->GetAbility(OwnerIndex,true);
				if(OwnerData && Interface->SetAbility(GetAbility(DistIndex), OwnerIndex))
				{
					Cast<ULostArcItemEquipBase>(GetAbility(DistIndex))->Dismount(Cast<ALostArcCharacter>(GetOwner()));
					SetAbility(OwnerData, DistIndex);
				}
			}
		}
	}
}
ULostArcAbilityBase* ULostArcCharacterEquipComponent::GetAbility(int32 SlotIndex, bool bTrans)
{
	if(bTrans)
	{
		auto TransUnit = Cast<ULostArcItemEquipBase>(GetAbility(SlotIndex));
		
		if(TransUnit != nullptr)
		{
			TransUnit->Dismount(Cast<ALostArcCharacter>(GetOwner()));
			EquipSlot.Find(IndexDecoding(SlotIndex))->EquipArray[SlotIndex] = nullptr;
			EquipSlotUpdate.Broadcast(IndexEncoding(TransUnit->GetAcType(), SlotIndex));
			return TransUnit;
		}
	
		return nullptr;
	}
	else
	{
		return EquipSlot.Find(IndexDecoding(SlotIndex))->EquipArray[SlotIndex];
	}
}
bool ULostArcCharacterEquipComponent::SetAbility(ULostArcAbilityBase* OwnerAbility, int32 SlotIndex)
{
	auto OwnerEquip = Cast<ULostArcItemEquipBase>(OwnerAbility);
	if(OwnerEquip == nullptr) return false;
	
	if(SlotIndex == -1)
	{
		for (int32 i = 0; i < *EquipMaxSlot.Find(OwnerEquip->GetAcType()); i++) // EquipSlot has Empty
		{
			if(EquipSlot.Find(OwnerEquip->GetAcType())->EquipArray[i] == nullptr)
			{
				EquipSlot.Find(OwnerEquip->GetAcType())->EquipArray[i] = OwnerEquip;
				EquipSlotUpdate.Broadcast(IndexEncoding(OwnerEquip->GetAcType(), i));
				return true;
			}
		}
		
		// EquipSlot has Fully
		// try swapping slot
		Swap(EquipSlot.Find(OwnerEquip->GetAcType())->EquipArray[0], OwnerEquip);
		if(Cast<ALostArcCharacter>(GetOwner())->InventoryComponent->SetAbility(OwnerEquip)) // 스왑 성공
		{
			OwnerEquip->Dismount(Cast<ALostArcCharacter>(GetOwner()));
			EquipSlotUpdate.Broadcast(IndexEncoding(OwnerEquip->GetAcType(), 0));
			return true;
		}
		else // 스왑 실패
		{
			Swap(EquipSlot.Find(OwnerEquip->GetAcType())->EquipArray[0], OwnerEquip);
			OwnerEquip->Dismount(Cast<ALostArcCharacter>(GetOwner()));
			return false;
		}
	}
	else // 인덱스에 삽입
	{
		if(IndexDecoding(SlotIndex, false) == OwnerEquip->GetAcType())
		{
			OwnerEquip->Equipment(Cast<ALostArcCharacter>(GetOwner()));
			EquipSlot.Find(IndexDecoding(SlotIndex))->EquipArray[SlotIndex] = OwnerEquip;
			EquipSlotUpdate.Broadcast(IndexEncoding(OwnerEquip->GetAcType(), SlotIndex));
			return true;
		}
		
		return false;
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
EAccessoryType ULostArcCharacterEquipComponent::IndexDecoding(int32& SlotIndex, bool bTrans)
{
	switch (SlotIndex)
	{
	case 0:
		return EAccessoryType::Necklace;
	case 1:
	case 2:
		if(bTrans)
			SlotIndex-=1;
		return EAccessoryType::Earring;
	case 3:
	case 4:
		if(bTrans)
			SlotIndex-=3;
		return EAccessoryType::Ring;
	}
	
	return EAccessoryType::Necklace;
}