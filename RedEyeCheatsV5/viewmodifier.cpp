#include "viewmodifier.h"
#include "variables.h"
#include "Functions.h"
#include "cBaseViewModel.h"
#include "inputManager.h"
void viewmodifier::run(CViewSetup* setup) {
	/*
	if (Menu::Window.VisualsTab.FreeCamKey.GetKey() != -1)
			{
				int freecamkey = Menu::Window.VisualsTab.FreeCamKey.GetKey();
				if (!GetAsyncKeyState(freecamkey))
					newOrigin = pSetup->origin;

				if (GetAsyncKeyState(freecamkey))
				{
					unsigned int fSpeed = 10.f; //5.f;
					if (GetAsyncKeyState(0x57)) // W		
						newOrigin += pSetup->angles.Forward() * fSpeed;


					if (GetAsyncKeyState(0x41)) // A		
						newOrigin += pSetup->angles.Right() * fSpeed;

					if (GetAsyncKeyState(0x44)) // D		
						newOrigin -= pSetup->angles.Right() * fSpeed;

					if (GetAsyncKeyState(0x53)) // S		
						newOrigin -= pSetup->angles.Forward() * fSpeed;

					if (GetAsyncKeyState(VK_SPACE)) // Space		
						newOrigin += pSetup->angles.Up() * fSpeed;

					pSetup->origin = newOrigin;
				}
			}
			if (Menu::Window.VisualsTab.FreeLookKey.GetKey() != -1)
			{
				if (GetAsyncKeyState(Menu::Window.VisualsTab.FreeLookKey.GetKey()) && !FreeLook::VirualViewAngles.IsZero()) {
					pSetup->angles.x = FreeLook::VirualViewAngles.x;
					pSetup->angles.y = FreeLook::VirualViewAngles.y;
				}
			}
			if (Menu::Window.VisualsTab.MirrorViewKey.GetKey() != -1)
			{
				if (GetAsyncKeyState(Menu::Window.VisualsTab.MirrorViewKey.GetKey())) {
					
					pSetup->angles.y += 180.0f; //rotate yaw;
				}
			}
			if (Menu::Window.VisualsTab.MapHeightKey.GetKey() != -1)
			{
				if (GetAsyncKeyState(Menu::Window.VisualsTab.MapHeightKey.GetKey())) {

					pSetup->origin.z += 300; //rotate yaw;
				}
			}
	*/
	if (variables::misc::mirrorview != -1 && inputmanager.hold(variables::misc::mirrorview)) {
		if (mirrorRotation < 180)
			mirrorRotation = Functions::clip(mirrorRotation + 13, 0, 180);
	}
	else {
		if (mirrorRotation > 0)
			mirrorRotation = Functions::clip(mirrorRotation - 13, 0, 180);
	}
	if (mirrorRotation > 0) { 
		setup->angles.y += mirrorRotation;
	}


	if (variables::misc::mapheight != -1 && inputmanager.hold(variables::misc::mapheight)) {
		if (mapRaise < 300)
			mapRaise = Functions::clip(mapRaise + 20, 0, 300);
	}
	else {
		if (mapRaise > 0)
			mapRaise = Functions::clip(mapRaise - 20, 0, 300);
	}
	if (mapRaise > 0) {
		setup->origin.z += mapRaise;
	}
	
	if (variables::misc::freemove != -1 && inputmanager.hold(variables::misc::freemove)) {
		
		if (inputmanager.hold(0x57)) // W		
			origin += setup->angles.Forward() * 10.f;
		if (inputmanager.hold(0x41)) // A		
			origin += setup->angles.Right() * 10.f;
		if (inputmanager.hold(0x44)) // D		
			origin -= setup->angles.Right() * 10.f;
		if (inputmanager.hold(0x53)) // S		
			origin -= setup->angles.Forward() * 10.f;
		if (inputmanager.hold(VK_SPACE))	
			origin += setup->angles.Up() * 10.f;

		setup->origin = origin;
	}
	else
		origin = setup->origin;
}