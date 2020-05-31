#ifndef CG_TP_ENGINE_SRC_UTIL_SETTINGS_H_
#define CG_TP_ENGINE_SRC_UTIL_SETTINGS_H_

#include <map>
#include <string>

namespace engine {
    /**
     * Classe de utilidade que permite a existência de definições globais acessíveis na aplicação toda.
     */
    class Settings {
    private:
        static std::map<const std::string, std::string> settings;

    public:
        static bool Contains(const std::string& key);
        static std::string Get(const std::string& key);
        static void Set(const std::string& key, const std::string& value);
        static void Delete(const std::string& key);
    };
}

#endif //CG_TP_ENGINE_SRC_UTIL_SETTINGS_H_
