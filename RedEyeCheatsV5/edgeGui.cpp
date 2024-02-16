#include "edgeGui.h"
#include <iostream> 
#include <fstream>
#include "edgeAim.h"
namespace FU
{
	void null() {

	}
	void FullUpdate() {
		Que::NextFullupdate = true;
	}
}
namespace MENU {
	void updateScaleFactor() {
		Game::menu_scale_factor = (variables::gui::scaleFactor / 100.f);
	}
}
namespace SETTINGS {

	void RenameConfig() {
		if (ConfigurationFileAlreadyExists(m_sName)) return;
		std::string oldName = Configurations[m_iSelectedIndex];
		std::string ab = path.c_str() + oldName + ".ini";
		std::ifstream a(ab);
		std::string contents = Functions::getFileContents(a);
		Functions::FindReplace(contents, oldName, m_sName);
		remove(ab.c_str());
		Configurations[m_iSelectedIndex] = m_sName;
		std::ofstream outfile(path + m_sName + ".ini");
		outfile << contents << std::endl;
		outfile.close();
		

	}
	/*void LoadSetting()
	{
		std::string m_sSettingDirectory = path + xorStr("csgoconfigs.ini");
		if (!FileExists(m_sSettingDirectory.c_str())) {
			SaveSetting();
		}
		RefreshSettings();
	}*/
	std::string path = "";
	std::vector <std::string> Configurations;
	std::string m_sName = xorStr("New Configuration");
	std::string m_sDefaultName = xorStr("REC");
	int m_iSelectedIndex = 0;
	void setupPath() {
		char* appdata = getenv(xorStr("APPDATA"));
		std::string dir = appdata; dir += xorStr("\\VPXA_3432\\");
		path = dir;
	}
	bool FileExists(const char* _path)
	{
		std::ifstream infile(_path);
		bool good = infile.good();
		infile.close();
		return good;
	}

	void SaveSetting()
	{
		if (!FileExists(path.c_str()))
			CreateDirectory(path.c_str(), NULL);
		std::string m_sSettingDirectory = path + xorStr("csgoconfigs.ini");
		if (FileExists(m_sSettingDirectory.c_str()))
			remove(m_sSettingDirectory.c_str());
		std::ofstream a(m_sSettingDirectory.c_str());
		WritePrivateProfileString(xorStr("Default Configuration"), xorStr("Name"), m_sDefaultName.c_str(), m_sSettingDirectory.c_str());
		a.close();
		return;
	}
	std::vector<std::string> get_all_files_names_within_folder(std::string folder)
	{
		std::vector<std::string> names;
		std::string search_path = folder + "/*.*";
		WIN32_FIND_DATA fd;
		HANDLE hFind = ::FindFirstFile(search_path.c_str(), &fd);
		if (hFind != INVALID_HANDLE_VALUE) {
			do {
				if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
					names.push_back(fd.cFileName);
				}
			} while (::FindNextFile(hFind, &fd));
			::FindClose(hFind);
		}
		return names;
	}
	bool ConfigurationFileAlreadyExists(std::string name)
	{
		std::vector<std::string> Files = get_all_files_names_within_folder(path);
		std::vector<std::string> Filtered = {};
		for (int i = 0; i < Files.size(); i++) {
			std::string file = Files[i];
			if (file.find(".ini") == std::string::npos) continue;
			if (file.find("csgoconfigs.ini") != std::string::npos) continue;
			if (file.find(xorStr("x37nawdui.ini")) != std::string::npos) continue;
			file.erase(file.begin() + file.size() - 4, file.end());
			if (file == name)
				return true;

		}
		return false;
	}
	void RefreshSettings()
	{
		std::vector<std::string> Files = get_all_files_names_within_folder(path);
		std::vector<std::string> Filtered = {};
		for (int i = 0; i < Files.size(); i++) {
			std::string file = Files[i];
			if (file.find(xorStr(".ini")) == std::string::npos) continue;
			if (file.find(xorStr("csgoconfigs.ini")) != std::string::npos) continue;
			if (file.find(xorStr("x37nawdui.ini")) != std::string::npos) continue;
			file.erase(file.begin() + file.size() - 4, file.end());
			Filtered.push_back(file);
		}
		Configurations.clear();
		for (int i = 0; i < Filtered.size(); i++) {
			Configurations.push_back(Filtered[i]);
		}
	}
	void  NewConfiguration()
	{
		if (ConfigurationFileAlreadyExists(m_sName)) return;
		SaveConfiguration(m_sName);
		RefreshSettings();
	}
	void LoadSetting()
	{
		std::string m_sSettingDirectory = path + xorStr("csgoconfigs.ini");
		if (!FileExists(m_sSettingDirectory.c_str())) {
			SaveSetting();
		}
		RefreshSettings();
		CHAR m_iPredictedDefault[128];
		GetPrivateProfileString(xorStr("Default Configuration"), xorStr("Name"), "", m_iPredictedDefault, 128, m_sSettingDirectory.c_str());
		if (m_iPredictedDefault != "") {
			bool Falsify = false;
			for (int i = 0; i < Configurations.size(); i++) {
				if (Configurations[i] != m_iPredictedDefault)
					Falsify = true;
			}
			if (Falsify) {
				m_sDefaultName = xorStr("");
				SaveSetting();
			}
			else {
				m_sDefaultName = m_iPredictedDefault;
				LoadConfiguration(m_sDefaultName);

			}
		}
	}

	void DeleteConfiguration(std::string name)
	{



		std::string m_sConfigurationDirectory = path + name + xorStr(".ini");
		remove(m_sConfigurationDirectory.c_str());

		if (m_sDefaultName != xorStr("") && m_sDefaultName == name) {
			m_sDefaultName = xorStr("");
			SaveSetting();
		}
		if (m_iSelectedIndex > 0) {
			m_iSelectedIndex--;
		}
		RefreshSettings();
		if (Configurations.size() == 0) {
			NewConfiguration();
			RefreshSettings();
		}
	}
	void DeleteConfiguration()
	{
		if (m_iSelectedIndex < Configurations.size()) {
			DeleteConfiguration(Configurations[m_iSelectedIndex]);
			SaveSetting();
		}
	}






	void LoadConfiguration(std::string name)
	{
		std::string m_sConfigurationDirectory = path + name + xorStr(".ini");
		if (!FileExists(m_sConfigurationDirectory.c_str())) {
			SaveConfiguration(name);
			return;
		}
		for (std::shared_ptr<edgeWindow> window : edgeaim.gui.Windows) {
			for (std::shared_ptr <edgeCluster> cluster : window->clusters) {
				for (std::shared_ptr <edgePage> page : cluster->pages) {
					for (std::shared_ptr <edgeControl> control : page->controls) {
						control->loadValue(m_sConfigurationDirectory.c_str(), window->name, name, cluster->name, page->name);
					}
				}
			}
		}
	}
	void LoadConfigurationz()
	{
		if (m_iSelectedIndex >= 0 && m_iSelectedIndex <= Configurations.size() && !Configurations.empty())
			LoadConfiguration(Configurations[m_iSelectedIndex]);

	}



	void SetDefault()
	{
		if (m_iSelectedIndex >= 0 && m_iSelectedIndex <= Configurations.size() && !Configurations.empty()) {
			m_sDefaultName = Configurations[m_iSelectedIndex];
			SaveSetting();
		}

	}

	void SaveConfiguration(std::string name)
	{
		CreateDirectory(path.c_str(), NULL);
		std::string m_sConfigurationDirectory = path + name + xorStr(".ini");
		if (FileExists(m_sConfigurationDirectory.c_str()))
			remove(m_sConfigurationDirectory.c_str());
		std::ofstream a(m_sConfigurationDirectory);
		for (std::shared_ptr<edgeWindow> window : edgeaim.gui.Windows) {
			for (std::shared_ptr <edgeCluster> cluster : window->clusters) {
				for (std::shared_ptr <edgePage> page : cluster->pages) {
					for (std::shared_ptr <edgeControl> control : page->controls) {
						control->saveValue(m_sConfigurationDirectory.c_str(), window->name, name, cluster->name, page->name);
					}
				}
			}
		}
		a.close();

	}
	void SaveConfigurationz()
	{

		if (m_iSelectedIndex >= 0 && m_iSelectedIndex <= Configurations.size() && !Configurations.empty())
			SaveConfiguration(Configurations[m_iSelectedIndex]);

	}
	
}
namespace DEBUG {
	void activate() {
		edgeaim.debugmanager.runDebugTest();
	}
}