#include "ObjectFactory.h"

#include "Enemy.h"
#include "Warrior.h"

ObjectFactory* ObjectFactory::s_Instance = nullptr;

GameObject* ObjectFactory::CreateObject(std::string type, Properties* props)
{
    GameObject* object = nullptr;
    auto it = m_TypeRegistry.find(type);

    if(it != m_TypeRegistry.end())
        object = it->second(props);

    return object;
}

void ObjectFactory::RegisterType(std::string className, std::function<GameObject*(Properties* props)> type)
{
    m_TypeRegistry[className] = type;
}

//ObjectFactory::ObjectFactory()
//{
//    //ctor
//}
