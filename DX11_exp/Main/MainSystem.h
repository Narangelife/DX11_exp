#pragma once

/// <summary>
/// ƒƒCƒ“ƒNƒ‰ƒX
/// </summary>
class MainSystem {

public:

	void Initialize();

	void Execute();

private:

	static inline MainSystem* s_instance;

	MainSystem() {};

public:

	static void CreateInstance() {
		DeleteInstance();
		s_instance = new MainSystem();
	}

	static void DeleteInstance() {
		if (s_instance != nullptr) {
			delete s_instance;
			s_instance = nullptr;
		}
	}

	static MainSystem& GetInstance() {
		return *s_instance;
	}

};

#define MAINSYS MainSystem::GetInstance()