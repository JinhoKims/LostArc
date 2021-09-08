// Fill out your copyright notice in the Description page of Project Settings.

#include "Component/LostArcCharacterEquipComponent.h"

#include "../../../../Plugins/Developer/RiderLink/Source/RD/thirdparty/spdlog/include/spdlog/fmt/bundled/format.h"
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
void ULostArcCharacterEquipComponent::SwappingSlot(int32 OwnerIndex, int32 DistIndex, UActorComponent* OwnerComponent)
{
	if(OwnerComponent == nullptr) // 내부 슬롯 스왑
	{
		if(GetAbility(OwnerIndex) == nullptr || OwnerIndex == DistIndex) return;
		auto Owner = OwnerIndex, Dist = DistIndex;
		
		if (GetAbility(DistIndex) == nullptr) // 이동
		{
			auto OwnerEquip = Cast<ULostArcItemEquipBase>(GetAbility(OwnerIndex));
			if(OwnerEquip->GetAcType() != IndexDecoding(DistIndex)) return;
			SetAbility(GetAbility(OwnerIndex,true), IndexEncoding(OwnerEquip->GetAcType(), DistIndex));
			UE_LOG(LogTemp,Warning,TEXT("Move Slot"));
		}
		else // 교체
		{
			auto OwnerType = IndexDecoding(OwnerIndex), DistType = IndexDecoding(DistIndex);
			Swap(EquipSlot.Find(OwnerType)->EquipArray[OwnerIndex], EquipSlot.Find(DistType)->EquipArray[DistIndex]);
			UE_LOG(LogTemp,Warning,TEXT("Swap Slot"));

			EquipSlotUpdate.Broadcast(Owner);
			EquipSlotUpdate.Broadcast(Dist);
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
		auto TransUnit = Cast<ULostArcItemEquipBase>(GetAbility(SlotIndex, false));
		
		if(TransUnit != nullptr)
		{
			TransUnit->Dismount(Cast<ALostArcCharacter>(GetOwner()));
			auto SlotType = IndexDecoding(SlotIndex);
			EquipSlot.Find(SlotType)->EquipArray[SlotIndex] = nullptr; // RValue에 nullptr을 직접 할당할 수는 없으니 Decoding 해줘야한다.
			EquipSlotUpdate.Broadcast(IndexEncoding(SlotType, SlotIndex));
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
		return EquipMounts(OwnerEquip);
	}
	else
	{
		auto DistType = IndexDecoding(SlotIndex);

		if(DistType == OwnerEquip->GetAcType())
		{
			EquipSlot.Find(DistType)->EquipArray[SlotIndex] = OwnerEquip;
			EquipSlot.Find(DistType)->EquipArray[SlotIndex]->Equipment(Cast<ALostArcCharacter>(GetOwner()));
			EquipSlotUpdate.Broadcast(IndexEncoding(DistType, SlotIndex));
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
bool ULostArcCharacterEquipComponent::EquipMounts(ULostArcItemEquipBase* NewEquip) // 이미 능력치가 증가된 상태임!!
{ // 최종적으로 SetAbility()으로 교체하기 (EquipBase 클래스도 멤버로 Interface를 선언하여 EquipComponent를 캐스팅해서 EquipMounts 대신 호출하도록...)
	if (NewEquip == nullptr) return false;
	
	for (int32 i = 0; i < *EquipMaxSlot.Find(NewEquip->GetAcType()); i++) // EquipSlot has Empty
		{
		if(EquipSlot.Find(NewEquip->GetAcType())->EquipArray[i] == nullptr)
		{
			EquipSlot.Find(NewEquip->GetAcType())->EquipArray[i] = NewEquip;
			EquipSlotUpdate.Broadcast(IndexEncoding(NewEquip->GetAcType(), i));
			return true;
		}
		}

	// EquipSlot has Fully
	Swap(EquipSlot.Find(NewEquip->GetAcType())->EquipArray[0], NewEquip);
	if(Cast<ALostArcCharacter>(GetOwner())->InventoryComponent->SetSlotData(NewEquip)) // 스왑 성공
		{
		NewEquip->Dismount(Cast<ALostArcCharacter>(GetOwner()));
		EquipSlotUpdate.Broadcast(IndexEncoding(NewEquip->GetAcType(), 0));
		return true;
		}
	else // 스왑 실패
		{
		Swap(EquipSlot.Find(NewEquip->GetAcType())->EquipArray[0], NewEquip);
		NewEquip->Dismount(Cast<ALostArcCharacter>(GetOwner()));
		return false;
		}
}

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


