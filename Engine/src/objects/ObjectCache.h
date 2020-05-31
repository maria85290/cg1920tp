#ifndef CG_TP_ENGINE_SRC_GLOBJECTS_OBJECTCACHE_H_
#define CG_TP_ENGINE_SRC_GLOBJECTS_OBJECTCACHE_H_

#include <map>
#include <memory>
#include <string>

namespace engine::objects {
    /**
     * Este template é responsável pela implementação do sistema de cache utilizado por
     * recursos partilhados entre várias tags XML, como por exemplo os modelos e as texturas.
     *
     * Esta classe implementa operações básicas de uma cache, com recurso a \code shared_ptr.
     *
     * @tparam T O tipo de objeto que vai ser partilhado
     */
	template<class T>
    class ObjectCache {
    private:
        std::map<const std::string, std::shared_ptr<T>> objects;

    public:
        ObjectCache() = default;
        ~ObjectCache() = default;

        ObjectCache(const ObjectCache& other) = delete;
        ObjectCache& operator=(const ObjectCache& other) = delete;

        std::shared_ptr<T> Insert(const std::string& key, T* const value) {
            auto elem = std::shared_ptr<T>(value);

            this->objects[key] = elem;

            return std::shared_ptr<T>(elem);
        }

        bool Contains(const std::string key) const {
            return this->objects.count(key) > 0;
        }

        std::shared_ptr<T> Retrieve(const std::string key) const {
            if(!this->Contains(key)) {
                return nullptr;
            }

            return std::shared_ptr<T>(this->objects.find(key)->second);
        }

        bool Delete(std::string key) {
            if(!this->Contains(key)) {
                return false;
            }

            this->objects.erase(key);

            return true;
        }

        inline void Clear() {
            this->objects.clear();
        }
    };
}

#endif //CG_TP_ENGINE_SRC_GLOBJECTS_OBJECTCACHE_H_
