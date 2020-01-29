#include <HunspellExt.hpp>

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
