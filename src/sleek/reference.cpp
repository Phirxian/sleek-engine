#include "reference.h"

namespace sleek
{
    reference::reference(const u32 i) noexcept
        : id(i), TypeName(getSerialiseName())
    {
    }
    reference::~reference() noexcept
    {
    }
    /** ******************************** **/
    void reference::operator += (reference *_new) noexcept
    {
        addBloc(_new);
    }
    void reference::egals(const reference *other) noexcept
    {
        clear();
        for(u32 i = 0; i<other->getNumberAttribute(); ++i)
            addAttribute(other->info[i].name, other->info[i].value);
        for(u32 i = 0; i<other->getNumberBloc(); ++i)
            addBloc(other->getBloc(i));
    }
    void reference::clear() noexcept
    {
        clearAttribute();
        clearBloc();
    }
    void reference::clearAttribute() noexcept
    {
        info.clear();
    }
    void reference::clearBloc() noexcept
    {
        bloc.clear();
    }
    /** ******************************** **/
    void reference::addBloc(reference *_new) noexcept
    {
        bloc.push_back(_new);
    }
    reference* reference::getBloc(const u32 index) const noexcept
    {
        return getNumberBloc() < index ? bloc[index] : 0;
    }
    reference* reference::getBloc(const std::string &name) const noexcept
    {
        for(u32 i = 0; i<getNumberBloc(); ++i)
            if(getBloc(i) && getBloc(i)->getSerialiseName() == name) return bloc[i];
        return 0;
    }
    void reference::removeBloc(const std::string &name) noexcept
    {
        for(u32 i = 0; i<getNumberBloc(); ++i)
            if(getBloc(i) && getBloc(i)->getSerialiseName() == name) removeBloc(i);
    }
    void reference::removeBloc(const u32 index) noexcept
    {
        int i = 0;
        for(auto it = bloc.begin(); it != bloc.end(); ++it)
        {
            if(i == index)
            {
                bloc.erase(it);
                break;
            }
        }
    }
    u32 reference::getNumberBloc() const noexcept
    {
        return bloc.size();
    }
    /** ******************************** **/
    void reference::addAttribute(const std::string &name, const std::string &value) noexcept
    {
        attribute tmp(name, value);
        info.push_back(tmp);
    }
    std::string reference::getAttribute(const std::string &name) const noexcept
    {
        for(u32 i = 0; i<getNumberAttribute(); ++i)
            if(info[i].name == name) return info[i].value;
        return "";
    }
    std::string reference::getAttribute(const u32 index) const noexcept
    {
        return getNumberAttribute() < index ? info[index].value : "";
    }
    void reference::removeAttribute(const std::string &name) noexcept
    {
        for(u32 i = 0; i<getNumberAttribute(); ++i)
            if(info[i].name == name) removeAttribute(i);
    }
    void reference::removeAttribute(const u32 index) noexcept
    {
        int i = 0;
        for(auto it = info.begin(); it != info.end(); ++it)
        {
            if(i == index)
            {
                info.erase(it);
                break;
            }
        }
    }
    u32 reference::getNumberAttribute() const noexcept
    {
        return info.size();
    }
    /** ******************************** **/
    std::string reference::serialise(const char *tablature) const noexcept
    {
        std::string a, b(tablature);          b += "\t";
//            a += SerialiseBlocBegin(getSerialiseName(),tablature);
//            a += SerialiseLigne("NumberAttribute",info.size(),b.c_str());
//            a += SerialiseLigne("NumberBloc",bloc.size(),b.c_str());
//            for(unsigned short It = 0; It < info.size(); ++It) a += SerialiseLigne(info[It].name, info[It].value,b.c_str());
//            for(unsigned short It = 0; It < bloc.size(); ++It) if(bloc[It])  a += bloc[It]->serialise(b.c_str());
//            a += SerialiseBlocEnd(getSerialiseName(),tablature);
        return a;
    }
    void reference::unserialise(const std::string &src) noexcept
    {
//        if(src.size() == 0) return;
//        long next_pos = src.find("NumberBloc")+10;
//        for(int i = 0; i < CharToInt(getSerialiseLigne(src,"NumberAttribute")); ++i)
//        {
//            attribute *Ent = new attribute("Undefined","Nothink");
//                long loc1 = src.find("<",next_pos)+1, loc2 = src.find(" value = \"",loc1);
//                Ent->name = src.subStr(loc1,loc2-loc1);
//                Ent->value = getSerialiseLigne(src,Ent->name);
//                addAttribute(Ent->name,Ent->value);
//                next_pos = loc2;
//            delete Ent;
//        }
//        for(int i = 0; i < CharToInt(getSerialiseLigne(src,"NumberBloc")); ++i)
//        {
//            reference *tmp = new reference();
//                tmp->TypeName = findNextBlocName(src,next_pos);
//                tmp->unserialise(getSerialiseBloc(src,tmp->TypeName,next_pos));
//            bloc.push_back(tmp);
//        }
    }
}
