#include "php-spellcheck-ext/VoikkoExt.hpp"

void VoikkoExt::__construct(Php::Parameters &params)
{   
    const char * initError;

    _handle = voikkoInit(&initError, params[0], params[1]);

    if (initError) {
        Php::out << "Error while initializing voikko: " << initError << std::endl;
    }
}

void VoikkoExt::__destruct()
{
    if (_handle) {
        voikkoTerminate(_handle);
    }
}

Php::Value VoikkoExt::check(Php::Parameters &params)
{
    return voikkoSpellCstr(_handle, params[0]);
}

Php::Value VoikkoExt::suggest(Php::Parameters &params)
{
    char ** suggestions = voikkoSuggestCstr(_handle, params[0]);

    if (suggestions) {
        int count = 0;
        
        while (suggestions[count]){
            count++;
        }

        return std::vector<std::string> (suggestions, suggestions + count);
    }

    return std::vector<std::string>();
}

Php::Class<VoikkoExt> VoikkoExt::getPhpClass()
{
    Php::Class<VoikkoExt> extClass("VoikkoExt");

    extClass.method<&VoikkoExt::__construct>("__construct", {
        Php::ByVal("languageCode", Php::Type::String, true),
        Php::ByVal("dictPath", Php::Type::String, true)
    });

    extClass.method<&VoikkoExt::__destruct>("__destruct");

    extClass.method<&VoikkoExt::check>("check", {
        Php::ByVal("word", Php::Type::String, true)
    });

    extClass.method<&VoikkoExt::suggest>("suggest", {
        Php::ByVal("word", Php::Type::String, true)
    });

    return extClass;
}