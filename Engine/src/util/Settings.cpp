#include "Settings.h"

using namespace std;

namespace engine {
    map<const string, string> Settings::settings;

    bool Settings::Contains(const string &key) {
        return settings.count(key) > 0;
    }

    string Settings::Get(const string& key) {
        if(settings.count(key) == -1)
            return nullptr;

        return settings[key];
    }

    void Settings::Set(const string& key, const string& value) {
        settings[key] = value;
    }

    void Settings::Delete(const string &key) {
        if(Settings::Contains(key))
            settings.erase(key);
    }
}
