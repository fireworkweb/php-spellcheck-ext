#include "php-spellcheck-ext/HunspellExt.hpp"

void HunspellExt::__construct(Php::Parameters &params)
{  
    _hunspell = new Hunspell(params[0], params[1]);
}

void HunspellExt::__destruct()
{
    delete _hunspell;
}

Php::Value HunspellExt::check(Php::Parameters &params)
{
    std::string word = params[0];

    return _hunspell->spell(word.c_str());
}

Php::Value HunspellExt::suggest(Php::Parameters &params)
{
    std::string word = params[0];

    char **suggestions;

    int count = _hunspell->suggest(&suggestions, word.c_str());

    return std::vector<std::string>(suggestions, suggestions + count);
}

Php::Value HunspellExt::getWordChars()
{
    return _hunspell->get_wordchars_cpp();
}

Php::Class<HunspellExt> HunspellExt::getPhpClass()
{
    Php::Class<HunspellExt> extClass("HunspellExt");

    extClass.method<&HunspellExt::__construct>("__construct", {
        Php::ByVal("dicPath", Php::Type::String, true),
        Php::ByVal("affPath", Php::Type::String, true)
    });

    extClass.method<&HunspellExt::__destruct>("__destruct");

    extClass.method<&HunspellExt::check>("check", {
        Php::ByVal("word", Php::Type::String, true)
    });
    
    extClass.method<&HunspellExt::suggest>("suggest", {
        Php::ByVal("word", Php::Type::String, true)
    });

    extClass.method<&HunspellExt::getWordChars>("getWordChars");

    return extClass;
}
