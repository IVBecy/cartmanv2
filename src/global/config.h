namespace config {
	namespace misc {
		//// BHOP
		inline bool bunnyHop = false;
		inline bool autostrafe = false;
		//// Flash
		inline bool noFlash = false;
		//// Nade trajectory
		inline bool nadeTraject = false;
		//// Other
		inline bool showSniperCrosshair = false;
		//
		inline bool thirdPerson = false;
		inline float thirdPersonAngle = 125.f;
	}

	namespace visuals {
		//// Chams
		namespace chams {
			// Enemy
			inline bool __hiddenColoursEnemy = false;
			inline bool __visibleColoursEnemy = false;
			inline float hiddenColoursEnemy[3] = { 0.f,1.f,0.93f };
			inline float visibleColoursEnemy[3] = { 0.5f,1.f,0.f };

			// Weapon
			inline bool entity = false;
			inline float entityColours[3] = { 1.f,1.f,1.f };

			// Materials
			inline int playermaterial = 0;
			inline int enemymaterial = 0;
			inline const char* material[]{ "debug/debugambientcube",
			"models/extras/speech_info",
			"models/inventory_items/trophy_majors/crystal_blue",
			"models/inventory_items/trophy_majors/crystal_clear",
			"models/inventory_items/trophy_majors/gloss",
			};
		};
		
		//// Sky colour
		inline bool skyColour = false;
		inline float skyColours[3] = { 0.54f, 0.f, 0.82f };

		//// Sky box
		inline bool skyEnable = false;
		inline const char* skyName = "";
		inline int skyNew;
		inline const char* skyBoxes[] = { "cs_baggage_skybox_", "cs_tibet", "embassy", "italy", "jungle", "nukeblank", "office", "sky_cs15_daylight01_hdr", "sky_cs15_daylight02_hdr", "sky_cs15_daylight03_hdr", "sky_cs15_daylight04_hdr", "sky_csgo_cloudy01", "sky_csgo_night_flat", "sky_csgo_night02", "sky_day02_05_hdr", "sky_day02_05", "sky_dust", "sky_l4d_rural02_ldr", "sky_venice", "vertigo_hdr", "vertigo", "vertigoblue_hdr", "vietnam" ,"sky_lunacy"};
	
		// Hit Marker
		inline float hitTime;
		inline int hitMarkerSize = 9;
		inline bool hitMarkerToggle = false;

	}
	
	namespace aim {
		//// RCS
		inline bool rcs = false;
		//// Trigger
		inline bool trigger = false;
		// Aim bot
		inline bool aimbot = false;
		inline bool autoLock = false;
		inline float smooth = 0.f;
		inline float fov = 2.f;
		inline bool silent = false;
		inline bool autoAttack = false;
		inline int hitBoxChoice;
		inline const char* hitboxes[]{ "Head","Neck","Chest","Core"};
	}
	// ESP
	namespace esp {
		//// Box
		inline bool Box = false;
		inline bool BoxHealth = false;
		inline bool showName = false;
		inline bool showGun = false;
		inline bool snapLines = false;
	}
}