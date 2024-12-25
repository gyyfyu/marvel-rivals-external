#pragma once
#include "sdk.hpp"
#include <iostream>

using namespace Globals;
using namespace Camera;
using namespace UE4;

GWorld* UWorld;
GGameInstance* UGameInstance;
GLocalPlayer* ULocalPlayer;
GPlayerController* APlayerController;
GPawn* APawn;
GPrivatePawn* APrivatePawn;
GULevel* ULevel;
GUSkeletalMeshComponent* USkeletalMeshComponent;

bool cached = false;
uintptr_t WorldPtr;



auto CacheGame() -> void
{
	auto guardedregion = driver.guarded_region();

	while (true)
	{
		std::vector<ValEntity> CachedList;

		WorldPtr = driver.readv<uintptr_t>(0x7ff6f1670000 + 0x0DB27420);


		auto ULevelPtr = UWorld->ULevel(WorldPtr);

		auto gamestate = UWorld->gamestate(WorldPtr);


		auto UGameInstancePtr = UWorld->GameInstance(WorldPtr);

		auto ULocalPlayerPtr = UGameInstance->ULocalPlayer(UGameInstancePtr);
		auto APlayerControllerPtr = ULocalPlayer->APlayerController(ULocalPlayerPtr);

		PlayerCameraManager = APlayerController->APlayerCameraManager(APlayerControllerPtr);
		auto MyHUD = APlayerController->AHUD(APlayerControllerPtr);

		auto APawnPtr = APlayerController->APawn(APlayerControllerPtr);

		if (APawnPtr != 0)
		{
			MyUniqueID = APawn->UniqueID(APawnPtr);
			MyRelativeLocation = APawn->RelativeLocation(APawnPtr);
			//printf("MyRelativeLocation: x: %f, y: %f, z: %f\n", MyRelativeLocation.x, MyRelativeLocation.y, MyRelativeLocation.z);
			Sleep(1);
		}

		if (MyHUD != 0)
		{
			auto PlayerArray = ULevel->AActorArray(ULevelPtr);
			printf("entityList: %p\n", PlayerArray.Data);
			printf("entityList.Count: %u\n", PlayerArray.Count);
			printf("entityList.Max: %u\n", PlayerArray.Max);







			Sleep(1);

			


			for (uint32_t i = 0; i < PlayerArray.Count; ++i)
			{
				auto Pawns = PlayerArray[i];
				//printf("Pawns: %p\n", PlayerArray[i]);


				auto team_id = APawn->TeamID(Pawns);




				printf("team_id: %d\n", team_id);


				RandomPawnRelativeLocation = APawn->RelativeLocation(PlayerArray[i]);

				auto actor_id = driver.readv<int>(Pawns + 0x18);
				printf("actor_id: %d\n", actor_id);

				if (1)
					printf("RandomPawnRelativeLocation: x: %f, y: %f, z: %f\n", RandomPawnRelativeLocation.x, RandomPawnRelativeLocation.y, RandomPawnRelativeLocation.z);



				



				if (Pawns != APawnPtr)
				{
					if (1)
					{

						if (1) //13 is the enemy id
						{
						//printf("Pawns Like me: %p\n", Pawns);
						PawnLikeMeLocation = APawn->RelativeLocation(Pawns);
						printf("PawnLikeMeLocation: x: %f, y: %f, z: %f\n", PawnLikeMeLocation.x, PawnLikeMeLocation.y, PawnLikeMeLocation.z);


						ValEntity Entities{ Pawns };
						CachedList.push_back(Entities);

						}


					}
				}
			}

			ValList.clear();
			ValList = CachedList;
			Sleep(1000);
		}
	}
}

auto CheatLoop() -> void
{
	for (ValEntity ValEntityList : ValList)
	{
		auto SkeletalMesh = APrivatePawn->USkeletalMeshComponent(ValEntityList.Actor);

		auto RelativeLocation = APawn->RelativeLocation(ValEntityList.Actor);
		auto RelativeLocationProjected = UE4::SDK::ProjectWorldToScreen(RelativeLocation);


		auto RelativePosition = RelativeLocation - CameraLocation;
		auto RelativeDistance = RelativePosition.Length() / 10000 * 2;


		auto HeadBone = UE4::SDK::GetEntityBone(SkeletalMesh, 206);

		auto HeadBoneProjected = UE4::SDK::ProjectWorldToScreen(HeadBone);



		auto RootBone = UE4::SDK::GetEntityBone(SkeletalMesh, 99);

		auto RootBoneProjected = UE4::SDK::ProjectWorldToScreen(RootBone);
		auto RootBoneProjected2 = UE4::SDK::ProjectWorldToScreen(FVector(RootBone.x, RootBone.y, RootBone.z - 15));

		auto Distance = MyRelativeLocation.Distance(RelativeLocation);

		//printf("HeadBone.y %f\n", HeadBone.y);
		//printf("RootBone.y %f\n", RootBone.y);


		float BoxHeight = abs(HeadBoneProjected.y - RootBoneProjected.y+80);
		float BoxWidth = BoxHeight * 0.40;

		auto ESPColor = ImColor(255, 255, 255);

		auto Health = APawn->Health(ValEntityList.Actor);
		//if (Health <= 0) continue;

		if (1)
		{
			if (1)
				DrawTracers(RootBoneProjected, ESPColor);

			if (1)
				Draw2DBox(RelativeLocationProjected, BoxWidth, BoxHeight, ESPColor);

			if (1)
				DrawOutlinedBox(RelativeLocationProjected, BoxWidth, BoxHeight, ESPColor);

			if (1)
				DrawHealthBar(RelativeLocationProjected, BoxWidth, BoxHeight, Health, RelativeDistance);

			if (1)
				DrawDistance(RootBoneProjected2, Distance);
		}
	}
}
