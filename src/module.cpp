#include <HunspellExt.hpp>

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
        // static(!) Php::Extension object that should stay in memory
        // for the entire duration of the process (that's why it's static)
        static Php::Extension extension("hunspell-ext", "1.0");

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

        // add the class to the extension
        extension.add(std::move(extClass));

        // return the extension
        return extension;
    }
}