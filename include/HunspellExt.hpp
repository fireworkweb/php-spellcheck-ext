#include <hunspell/hunspell.hxx>
#include <phpcpp.h>
#include <vector>

class HunspellExt : public Php::Base
{
    private:
        Hunspell * _hunspell;
        
    public:
        HunspellExt() = default;

        virtual ~HunspellExt() = default;

        void __construct(Php::Parameters &params);

        void __destruct();

        Php::Value check(Php::Parameters &params);

        Php::Value suggest(Php::Parameters &params);

        Php::Value getWordChars();
};