#include <phpcpp.h>

#ifdef ENABLE_HUNSPELL
#include "php-spellcheck-ext/HunspellExt.hpp"
#endif

#ifdef ENABLE_VOIKKO
#include "php-spellcheck-ext/VoikkoExt.hpp"
#endif


/**
 *  tell the compiler that the get_module is a pure C function
 */
extern "C" {

    /**
     *  Function that is called by PHP right after the PHP process
     *  has started, and that returns an address of an internal PHP
     *  strucure with all the details and features of your extension
     *
     *  @return void*   a pointer to an address that is understood by PHP
     */
    PHPCPP_EXPORT void *get_module() 
    {
        static Php::Extension extension("spellcheck-ext", "1.0");

        Php::Namespace extNamespace("FireworkWeb");
        Php::Namespace spellCheckNamespace("Spellcheck");

        #ifdef ENABLE_HUNSPELL
        auto hunspell = std::move(HunspellExt::getPhpClass());

        spellCheckNamespace.add(hunspell);
        #endif

        #ifdef ENABLE_VOIKKO
        auto voikko = std::move(VoikkoExt::getPhpClass());

        spellCheckNamespace.add(voikko);
        #endif
        
        extNamespace.add(std::move(spellCheckNamespace));
        extension.add(std::move(extNamespace));

        return extension;
    }
}